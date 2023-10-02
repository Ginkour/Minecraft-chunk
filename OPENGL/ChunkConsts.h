#pragma once
#include "Container.h"
#include "Texture.h"
#include <vector>
namespace mge
{
    //enum class BlockType
    //{
    //    indestructable,
    //    plants,
    //    soil,
    //    wood,
    //    solid,
    //    glass
    //};
    const char* const terrain_path = "data/textures/terrain.png";
    const mge::Vector2u textureUnits = { 16, 16 };
    enum class BlockType           
    {
        air = -1,
        grass,
        stone,
        dirt,
        planks,
        cobblestone,
        moss_cobblestone,
        bedrock,
        sand,
        gravel,
        oak_log,
        oak_leaves,
        diamond_ore,
        pink_wool,
    };
    enum class Instrument
    {
        none,
        hand,
        sword,
        shovel,
        axe,
        pickaxe,
        hoe,
        scissors,
    };
    struct BlockData
    {
        mge::Vector2u texbottom;
        mge::Vector2u textop;
        mge::Vector2u texleft;
        mge::Vector2u texright;
        mge::Vector2u texback;
        mge::Vector2u texfront;


        mge::BlockType block;
        mge::Instrument instrument;


        float break_time;
    };
    enum class Face
    {
        bottom = 0,
        top = 1,
        left = 2,
        right = 3,
        back = 4,
        front = 5,
        inv_bottom = 6,
        inv_top = 7,
        inv_left = 8,
        inv_right = 9,
        inv_back = 10,
        inv_front = 11
    };
    const BlockData blocksData[] =
    {
        { {2, 0}, {0, 0}, {3, 0}, {3, 0}, {3, 0}, {3, 0}, BlockType::grass           , mge::Instrument::shovel,   0.30f},
        { {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, 0}, BlockType::stone           , mge::Instrument::pickaxe,  3.00f},
        { {2, 0}, {2, 0}, {2, 0}, {2, 0}, {2, 0}, {2, 0}, BlockType::dirt            , mge::Instrument::shovel,   0.25f},
        { {4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, {4, 0}, BlockType::planks          , mge::Instrument::axe,      1.00f},
        { {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, {0, 1}, BlockType::cobblestone     , mge::Instrument::pickaxe,  3.00f},
        { {4, 2}, {4, 2}, {4, 2}, {4, 2}, {4, 2}, {4, 2}, BlockType::moss_cobblestone, mge::Instrument::pickaxe,  3.00f},
        { {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, {1, 1}, BlockType::bedrock         , mge::Instrument::none,     0.10f},
        { {2, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 1}, {2, 1}, BlockType::sand            , mge::Instrument::shovel,   0.50f},
        { {3, 1}, {3, 1}, {3, 1}, {3, 1}, {3, 1}, {3, 1}, BlockType::gravel          , mge::Instrument::shovel,   0.50f},
        { {5, 1}, {5, 1}, {4, 1}, {4, 1}, {4, 1}, {4, 1}, BlockType::oak_log         , mge::Instrument::axe,      1.00f},
        { {5, 3}, {5, 3}, {5, 3}, {5, 3}, {5, 3}, {5, 3}, BlockType::oak_leaves      , mge::Instrument::axe,      0.25f},
        { {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, {2, 3}, BlockType::diamond_ore     , mge::Instrument::pickaxe,  5.00f},
        { {2, 8}, {2, 8}, {2, 8}, {2, 8}, {2, 8}, {2, 8}, BlockType::pink_wool       , mge::Instrument::scissors, 0.50f},
    };
    constexpr unsigned int blocksCount = sizeof(blocksData) / sizeof(BlockData);
    class TextureRectangle
    {
    public:
        mge::Vector2f t00;
        mge::Vector2f t01;
        mge::Vector2f t11;
        mge::Vector2f t10;
        TextureRectangle() : t00(0.f, 0.f), t01(0.f, 1.f), t11(1.f, 1.f), t10(1.f, 0.f) {}
        inline void setTextureRect(const mge::Vector2u& position, const mge::Vector2u& textureUnitsNumber)
        {
            // OpenGL texture from left bottom corner to right upper corner
            // Texture position from left upper corner to right bottom corner
            //      x1y2|x2y2 
            //      |1     2| Clockwise order
            //      |       | first triangle  0 1 2
            //      |0     3| second triangle 0 2 3
            //      x1y1|x2y1
            float y1 = 1.f - (float)(position.y + 1) / textureUnitsNumber.y; 
            float x1 = (float)position.x / textureUnitsNumber.x;
            float y2 = 1.f - (float)position.y / textureUnitsNumber.y;
            float x2 = (float)(position.x + 1) / textureUnitsNumber.x;
            t00 = { x1, y1 };
            t01 = { x1, y2 };
            t11 = { x2, y2 };
            t10 = { x2, y1 };
        }
    };
    class Block
    {
    private:
        mge::TextureRectangle meshTextureCoordinates[6];
        mge::BlockType m_blockType;
        mge::Instrument m_instrumentType;
        float m_breakTime;
        inline void initBlock(const mge::BlockData& blockData)
        {
            const mge::Vector2u* texturePositions = &blockData.texbottom;
            for (unsigned int i = 0; i < 6; i++)
            {
                meshTextureCoordinates[i].setTextureRect(texturePositions[i], mge::textureUnits);
            }
            m_instrumentType = blockData.instrument;
            m_blockType = blockData.block;
            m_breakTime = blockData.break_time;
        };
    public:
        inline const mge::TextureRectangle* getTextureRect() const
        {
            return meshTextureCoordinates;
        }
        inline const mge::BlockType getBlockType() const
        {
            return m_blockType;
        }
        inline const mge::Instrument getInstrumentType() const
        {
            return m_instrumentType;
        }
        inline const float getBreakTime() const
        {
            return m_breakTime;
        }
        friend class Blocks;
    };
    class Blocks 
    {
    private:
        mge::Block m_blocks [blocksCount];
    public:
        mge::Texture* terrainAtlas;
        inline const mge::Block& getBlock(BlockType block) const
        {
            return m_blocks[(int)block];
        }
    public:
        Blocks() :
            terrainAtlas(nullptr)
        {
            terrainAtlas = new mge::Texture(terrain_path, false, false, true);
            for (unsigned int i = 0; i < blocksCount; i++)
            {
                m_blocks[i].initBlock(blocksData[i]);
            }
        }
        ~Blocks() 
        {
            delete terrainAtlas;
        }
    };
}