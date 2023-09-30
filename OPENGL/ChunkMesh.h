#pragma once
#include "ChunkConsts.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <map>
namespace mge 
{
    struct BlockVertexData
    {
        mge::Vector3f v[8];
        BlockVertexData(mge::Vector2i chunkPos, mge::Vector3i pos)
        {
            float xy = (float)(chunkPos.x + pos.x);
            float xy1 = (float)(chunkPos.x + pos.x) + 1.f;
            float yz = (float)(chunkPos.y + pos.z);
            float yz1 = (float)(chunkPos.y + pos.z) + 1.f;
            float y = (float)pos.y;
            float y1 = (float)pos.y + 1.f;
            v[0] = mge::Vector3f(xy, y, yz);
            v[1] = mge::Vector3f(xy1, y, yz);
            v[2] = mge::Vector3f(xy1, y, yz1);
            v[3] = mge::Vector3f(xy, y, yz1);
            v[4] = mge::Vector3f(xy, y1, yz);
            v[5] = mge::Vector3f(xy1, y1, yz);
            v[6] = mge::Vector3f(xy1, y1, yz1);
            v[7] = mge::Vector3f(xy, y1, yz1);
        }
    };
    /// <summary>
    /// NC for NO COLOR
    /// </summary>
    struct vec3uc
    {
        unsigned char x = 0, y = 0, z = 0;
    };
    struct Vertex3NC
    {
        mge::Vector3f pos;
        mge::Vector2f texCoord;
    };
    struct Mesh
    {
        mge::Vertex3NC m_vert[4]; 
        Mesh(
            const mge::Vector3f& pos0, const mge::Vector2f& tex0,
            const mge::Vector3f& pos1, const mge::Vector2f& tex1,
            const mge::Vector3f& pos2, const mge::Vector2f& tex2,
            const mge::Vector3f& pos3, const mge::Vector2f& tex3)
        {
            m_vert[0].pos = pos0;
            m_vert[0].texCoord = tex0;

            m_vert[1].pos = pos1;
            m_vert[1].texCoord = tex1;

            m_vert[2].pos = pos2;
            m_vert[2].texCoord = tex2;

            m_vert[3].pos = pos3;
            m_vert[3].texCoord = tex3;
        }
        Mesh() {}
    };
    const unsigned int chunk_x = 16;
    const unsigned int chunk_y = 64;
    const unsigned int chunk_z = 16;
    const unsigned int chunkMaxBlocksSize = chunk_x * chunk_y * chunk_z;
    const unsigned int chunkMeshesSize = (chunkMaxBlocksSize * sizeof(mge::Mesh) * 6);// / 24;
    const unsigned int chunkIndecesCount  = chunkMeshesSize * 6;
    class FaceData
    {
    private:
        // to store memory efficiently but performance is going to be bad
        unsigned char visibilityByte = 0;
        // Faces meshes possition array for one block
        unsigned int vecPos[6] = { 0, 0, 0, 0, 0, 0 };
    public:
        inline bool isAny() const
        {
            return visibilityByte != 0;
        }
        inline bool isVisible(const unsigned char face) const
        {
            return (0x00000001 << face) & visibilityByte;
        }
        inline unsigned int getPos(const unsigned char face) const
        {
            return vecPos[face];
        }
        inline void setVisible(const unsigned char face, const unsigned int vecIndex)
        {
            visibilityByte |= 0x00000001 << face;
            vecPos[face] = vecIndex;
        }
        inline void unset(const unsigned char face)
        {
            visibilityByte &= ~(0x00000001 << face);
            vecPos[face] = 0;
        }
        // should be visible before calling
        inline void reset(const unsigned char face, const unsigned int index)
        {
            vecPos[face] = index;
        }
    };
    struct AddableBlock 
    {
        unsigned int index;
        mge::BlockType bt;
    };
    class ChunkMesh
    {
    public:
        mge::VertexArray m_chunkArray;
        mge::VertexBuffer m_chunkVertexBuffer;
        mge::IndexBuffer m_chunkIndexBuffer;

        mge::Vector2i m_chunkPos;
        std::vector<AddableBlock> added;
        std::vector<unsigned int> deleted;
        std::vector <mge::Mesh>     m_cubes;
        std::vector <unsigned int>  m_indeces;
        //std::map<unsigned int, unsigned int> faceMap;
        std::vector <mge::FaceData> facesdata;

        mge::BlockType* m_chunkSection_p;
        const mge::Blocks& blocksDataSingleton;
        bool updated = false;
        void addFace(const mge::BlockVertexData& v, const mge::TextureRectangle* rect, mge::Face face, unsigned int index)
        {
            if ((unsigned int)face < 6)
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
            switch (face)
            {
            case Face::bottom:
                m_cubes.emplace_back(
                    v.v[3], rect[static_cast<unsigned int>(face)].t00,
                    v.v[0], rect[static_cast<unsigned int>(face)].t01,
                    v.v[1], rect[static_cast<unsigned int>(face)].t11,
                    v.v[2], rect[static_cast<unsigned int>(face)].t10
                );
                break;

            case Face::inv_bottom:
                face = mge::Face::top;
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
                m_cubes.emplace_back(
                    v.v[3], rect[static_cast<unsigned int>(face)].t00,
                    v.v[2], rect[static_cast<unsigned int>(face)].t10,
                    v.v[1], rect[static_cast<unsigned int>(face)].t11,
                    v.v[0], rect[static_cast<unsigned int>(face)].t01
                );
                break;
            case Face::top:
                m_cubes.emplace_back(
                    v.v[4], rect[static_cast<unsigned int>(face)].t00,
                    v.v[7], rect[static_cast<unsigned int>(face)].t01,
                    v.v[6], rect[static_cast<unsigned int>(face)].t11,
                    v.v[5], rect[static_cast<unsigned int>(face)].t10
                );
                break;
            case Face::inv_top:
                face = mge::Face::bottom;
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
                m_cubes.emplace_back(
                    v.v[4], rect[static_cast<unsigned int>(face)].t00,
                    v.v[5], rect[static_cast<unsigned int>(face)].t10,
                    v.v[6], rect[static_cast<unsigned int>(face)].t11,
                    v.v[7], rect[static_cast<unsigned int>(face)].t01
                );
                break;
            case Face::left:
                m_cubes.emplace_back(
                    v.v[3], rect[static_cast<unsigned int>(face)].t00,
                    v.v[7], rect[static_cast<unsigned int>(face)].t01,
                    v.v[4], rect[static_cast<unsigned int>(face)].t11,
                    v.v[0], rect[static_cast<unsigned int>(face)].t10
                );
                break;
            case Face::inv_left:
                face = mge::Face::right;
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
                m_cubes.emplace_back(
                    v.v[3], rect[static_cast<unsigned int>(face)].t00,
                    v.v[0], rect[static_cast<unsigned int>(face)].t10,
                    v.v[4], rect[static_cast<unsigned int>(face)].t11,
                    v.v[7], rect[static_cast<unsigned int>(face)].t01
                );
                break;
            case Face::right:
                m_cubes.emplace_back(
                    v.v[1], rect[static_cast<unsigned int>(face)].t00,
                    v.v[5], rect[static_cast<unsigned int>(face)].t01,
                    v.v[6], rect[static_cast<unsigned int>(face)].t11,
                    v.v[2], rect[static_cast<unsigned int>(face)].t10
                );
                break;
            case Face::inv_right:
                face = mge::Face::left;
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
                m_cubes.emplace_back(
                    v.v[1], rect[static_cast<unsigned int>(face)].t00,
                    v.v[2], rect[static_cast<unsigned int>(face)].t10,
                    v.v[6], rect[static_cast<unsigned int>(face)].t11,
                    v.v[5], rect[static_cast<unsigned int>(face)].t01
                );
                break;
            case Face::back:
                m_cubes.emplace_back(
                    v.v[2], rect[static_cast<unsigned int>(face)].t00,
                    v.v[6], rect[static_cast<unsigned int>(face)].t01,
                    v.v[7], rect[static_cast<unsigned int>(face)].t11,
                    v.v[3], rect[static_cast<unsigned int>(face)].t10
                );
                break;
            case Face::inv_back:
                face = mge::Face::front;
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
                m_cubes.emplace_back(
                    v.v[2], rect[static_cast<unsigned int>(face)].t00,
                    v.v[3], rect[static_cast<unsigned int>(face)].t10,
                    v.v[7], rect[static_cast<unsigned int>(face)].t11,
                    v.v[6], rect[static_cast<unsigned int>(face)].t01
                );
                break;
            case Face::front:
                m_cubes.emplace_back(
                    v.v[0], rect[static_cast<unsigned int>(face)].t00,
                    v.v[4], rect[static_cast<unsigned int>(face)].t01,
                    v.v[5], rect[static_cast<unsigned int>(face)].t11,
                    v.v[1], rect[static_cast<unsigned int>(face)].t10
                );
                break;
            case Face::inv_front:
                face = mge::Face::back;
                if (facesdata.at(index).isVisible(((unsigned char)face)))
                    return;
                m_cubes.emplace_back(
                    v.v[0], rect[static_cast<unsigned int>(face)].t00,
                    v.v[1], rect[static_cast<unsigned int>(face)].t10,
                    v.v[5], rect[static_cast<unsigned int>(face)].t11,
                    v.v[4], rect[static_cast<unsigned int>(face)].t01
                );
                break;
            default:
                return;
            }
            unsigned int _lastIndex = m_cubes.size() - 1;
            facesdata.at(index).setVisible((unsigned char)face, _lastIndex);
            //faceMap[index * 6 + static_cast<unsigned int>(face)] = _lastIndex;
            _lastIndex *= 4;
            m_indeces.emplace_back(_lastIndex);
            m_indeces.emplace_back(_lastIndex + 1);
            m_indeces.emplace_back(_lastIndex + 2);
            m_indeces.emplace_back(_lastIndex);
            m_indeces.emplace_back(_lastIndex + 2);
            m_indeces.emplace_back(_lastIndex + 3);
        }
        mge::Vector2u findLastIndex(std::vector<mge::FaceData>& facesdata, const unsigned int size)
        {
            //const unsigned int sizearr = facesdata.size();
            for (unsigned int m = facesdata.size() - 1; m > 0; --m)
            {
                if (facesdata.at(m).isAny())
                {
                    for (unsigned char k = 0; k < 6; k++)
                    {
                        if (facesdata.at(m).isVisible(k))
                        {
                            const unsigned int index = facesdata.at(m).getPos(k);
                            if (index == size - 1)
                                return { /*BLOCK INDEX*/m, /*FACE INDEX*/(unsigned int)k };
                        }
                    }
                }
            }
            if (facesdata.at(0).isAny())
            {
                for (unsigned char k = 0; k < 6; k++)
                {
                    if (facesdata.at(0).isVisible(k))
                    {
                        if (const unsigned int index = facesdata.at(0).getPos(k) == size - 1)
                            return { index, (unsigned int)k };
                    }
                }
            }
            return { 0, 0 };
            // it is when size is 0 and there is no need to implement it
            //std::cout << "Error, impossible(for a developer) behaviour, program is terminated!\n";
            //exit(-1);
        }
        void tryDeleteFace(mge::FaceData& face, unsigned char k)
        {
            if (face.isVisible(k))
            {
                // find the new index for the last face for the next iteration
                mge::Vector2u lastIndex = findLastIndex(facesdata, m_cubes.size());
                // Face data for the last blocks in array 
                mge::FaceData& Lastface = facesdata.at(lastIndex.x);
                //swap if current face is not at the end
                if (face.getPos(k) != m_cubes.size() - 1)
                {
                    mge::Mesh* deleted = &m_cubes.at(face.getPos(k));
                    mge::Mesh& last1 = m_cubes.at(Lastface.getPos(lastIndex.y));
                    mge::Mesh& last2 = m_cubes.back();
                    *deleted = m_cubes.at(Lastface.getPos(lastIndex.y));
                    // 
                    Lastface.reset(lastIndex.y, face.getPos(k));
                }
                // we replaced last vertex to the center of array swaping it with deleted face or if it is the last anywayy we are deleting
                m_cubes.pop_back();

                // erase(last 6 indeces); // should be in the final version
                m_indeces.erase(m_indeces.end() - 6, m_indeces.end());

                // remove visible vertex from block face data
                face.unset(k);
            }
            //const auto& it = faceMap.find(index * 6 + static_cast<unsigned int>(face));
            //if (it != faceMap.end())
            //{
            //    const auto& lastv = std::prev(faceMap.end());
            //    if (it != lastv)
            //    {
            //        const unsigned int mcsize = m_cubes.size() - 1;
            //        if (lastv->second == mcsize)
            //        {
            //            std::swap(m_cubes[it->second], m_cubes[lastv->second]);
            //            lastv->second = it->second;
            //        }
            //        else
            //        {
            //            unsigned int* lastptr = nullptr;
            //            int m = 2;
            //            while (m)
            //            {
            //                const auto& last = std::prev(faceMap.end(), m);
            //                lastptr = &last->second;
            //                if (*lastptr == mcsize)
            //                    break;
            //                ++m;
            //            }
            //            std::swap(m_cubes[it->second], m_cubes[*lastptr]);
            //            *lastptr = it->second;
            //        }
            //    }
            //    faceMap.erase(it);
            //    m_cubes.pop_back();
            //    m_indeces.erase(m_indeces.end() - 6, m_indeces.end());
            //}
        }
        void deleteVisibleFaces(unsigned int index)
        {
            // deletion test
            mge::FaceData& block = facesdata.at(index);
            if (block.isAny())
                for (unsigned char i = 0; i < 6; i++)
                {
                    tryDeleteFace(block, i);
                }
        }
        void addBlock(mge::Vector3i pos, mge::BlockType blockID)
        {
            if (pos.x >= 0 && pos.x < chunk_x && pos.y >= 0 && pos.y < chunk_y && pos.z >= 0 && pos.z < chunk_z)
            {
                int wzsq = chunk_x * chunk_z;
                int xwz = pos.x * chunk_z;
                int index = pos.y * wzsq + xwz + pos.z;
                if (index >= 0 && index < chunkMaxBlocksSize && m_chunkSection_p[index] == BlockType::air)
                {
                    const mge::BlockVertexData v(m_chunkPos, pos);

                    const mge::TextureRectangle* rect = blocksDataSingleton.getBlock(blockID).getTextureRect();
                    m_chunkSection_p[index] = blockID;
                    updated = false;
                    int top_block = (pos.y + 1);
                    int bottom_block = (pos.y - 1);
                    int left_block = (pos.x - 1);
                    int right_block = (pos.x + 1);
                    int back_block = (pos.z + 1);
                    int front_block = (pos.z - 1);

                    bool top_cond = top_block < chunk_y;
                    bool bottom_cond = bottom_block >= 0;
                    bool left_cond = left_block >= 0;
                    bool right_cond = right_block < chunk_x;
                    bool back_cond = back_block < chunk_z;
                    bool front_cond = front_block >= 0;

                    int top = top_block * wzsq + xwz + pos.z;
                    int bottom = bottom_block * wzsq + xwz + pos.z;
                    int left = pos.y * wzsq + left_block * chunk_z + pos.z;
                    int right = pos.y * wzsq + right_block * chunk_z + pos.z;
                    int back = pos.y * wzsq + xwz + back_block;
                    int front = pos.y * wzsq + xwz + front_block;

                    if (!(top_cond && m_chunkSection_p[top] != BlockType::air))
                        addFace(v, rect, mge::Face::top, index);
                    else
                        tryDeleteFace(facesdata.at(top), (unsigned char)mge::Face::bottom);

                    if (!(bottom_cond && m_chunkSection_p[bottom] != BlockType::air))
                        addFace(v, rect, mge::Face::bottom, index);
                    else
                        tryDeleteFace(facesdata.at(bottom), (unsigned char)mge::Face::top);

                    if (!(left_cond && m_chunkSection_p[left] != BlockType::air))
                        addFace(v, rect, mge::Face::left, index);
                    else
                        tryDeleteFace(facesdata.at(left), (unsigned char)mge::Face::right);

                    if (!(right_cond && m_chunkSection_p[right] != BlockType::air))
                        addFace(v, rect, mge::Face::right, index);
                    else
                        tryDeleteFace(facesdata.at(right), (unsigned char)mge::Face::left);

                    if (!(back_cond && m_chunkSection_p[back] != BlockType::air))
                        addFace(v, rect, mge::Face::back, index);
                    else
                        tryDeleteFace(facesdata.at(back), (unsigned char)mge::Face::front);

                    if (!(front_cond && m_chunkSection_p[front] != BlockType::air))
                        addFace(v, rect, mge::Face::front, index);
                    else
                        tryDeleteFace(facesdata.at(front), (unsigned char)mge::Face::back);
                }
            }
        }
        void UpdateThread()
        {
            while (true)
            {
                for (unsigned int i = 0; i < added.size(); i++)
                {
                    //addBlock(added.at(i));
                    added.pop_back();
                }
                for (unsigned int i = 0; i < deleted.size(); i++)
                {
                    deleteBlock(deleted.at(i));
                    deleted.pop_back();
                }
                if (!updated)
                {
                    m_chunkIndexBuffer.Update(m_indeces.data(), m_indeces.size() * sizeof(unsigned int));
                    m_chunkVertexBuffer.Update(m_cubes.data(), m_cubes.size() * sizeof(Mesh));
                    updated = true;
                }
            }
        }
        // position must be only inside the chunk
        void deleteBlock(mge::Vector3i pos)
        {
            if (pos.x >= 0 && pos.x < chunk_x && pos.y >= 0 && pos.y < chunk_y && pos.z >= 0 && pos.z < chunk_z)
            {
                int wzsq = chunk_x * chunk_z;
                int xwz = pos.x * chunk_z;
                int index = pos.y * wzsq + xwz + pos.z;
                if (index >= 0 && index < chunkMaxBlocksSize && m_chunkSection_p[index] != BlockType::air)
                {
                    const mge::BlockVertexData v(m_chunkPos, pos);
                    m_chunkSection_p[index] = BlockType::air;
                    deleteVisibleFaces(index);
                    updated = false;


                    int top_block    = pos.y + 1;
                    int bottom_block = pos.y - 1;
                    
                    int right_block  = pos.x + 1;
                    int left_block   = pos.x - 1;
                    
                    int back_block   = pos.z + 1;
                    int front_block  = pos.z - 1;


                    bool top_cond    = top_block    <  chunk_y;
                    bool bottom_cond = bottom_block >= 0;

                    bool right_cond  = right_block  <  chunk_x;
                    bool left_cond   = left_block   >= 0;

                    bool back_cond   = back_block   <  chunk_z;
                    bool front_cond  = front_block  >= 0;


                    int top     = top_block    * wzsq + xwz + pos.z;
                    int bottom  = bottom_block * wzsq + xwz + pos.z;

                    int right   = pos.y * wzsq + right_block * chunk_z + pos.z;
                    int left    = pos.y * wzsq + left_block  * chunk_z + pos.z;
 
                    int back    = pos.y * wzsq + xwz + back_block;
                    int front   = pos.y * wzsq + xwz + front_block;


                    if (top_cond && m_chunkSection_p[top] != BlockType::air)
                        addFace(v, blocksDataSingleton.getBlock(m_chunkSection_p[top]).getTextureRect(), mge::Face::inv_top, top);

                    if (bottom_cond && m_chunkSection_p[bottom] != BlockType::air)
                        addFace(v, blocksDataSingleton.getBlock(m_chunkSection_p[bottom]).getTextureRect(), mge::Face::inv_bottom, bottom);

                    if (left_cond && m_chunkSection_p[left] != BlockType::air)
                        addFace(v, blocksDataSingleton.getBlock(m_chunkSection_p[left]).getTextureRect(), mge::Face::inv_left, left);

                    if (right_cond && m_chunkSection_p[right] != BlockType::air)
                        addFace(v, blocksDataSingleton.getBlock(m_chunkSection_p[right]).getTextureRect(), mge::Face::inv_right, right);

                    if (back_cond && m_chunkSection_p[back] != BlockType::air)
                        addFace(v, blocksDataSingleton.getBlock(m_chunkSection_p[back]).getTextureRect(), mge::Face::inv_back, back);

                    if (front_cond && m_chunkSection_p[front] != BlockType::air)
                        addFace(v, blocksDataSingleton.getBlock(m_chunkSection_p[front]).getTextureRect(), mge::Face::inv_front, front);
                }
            }
        }
        ChunkMesh(mge::BlockType* blockData, mge::Vector2i chunkPos, Blocks& blocls):
            blocksDataSingleton(blocls),
            m_chunkSection_p(blockData),
            m_chunkPos(chunkPos.x * (int)chunk_x, chunkPos.y * (int)chunk_z)
        { 
            m_cubes.reserve(chunkMaxBlocksSize * 6);
            m_indeces.reserve(chunkIndecesCount);
            facesdata.insert(facesdata.begin(), chunkMaxBlocksSize, {});
            //m_facesDataArray.reserve(chunkMaxBlocksSize);
            //m_facesDataArray.insert(m_facesDataArray.end(), chunkMaxBlocksSize, { 0 });
            //Read chunk
            int wzsq = chunk_x * chunk_z;
            for (int y = 0; y < chunk_y; ++y)
                for (int x = 0; x < chunk_z; ++x)
                    for (int z = 0; z < chunk_z; ++z)
                    {
                        int xwz = x * chunk_z;
                        int index = y * wzsq + xwz + z;
                        const mge::TextureRectangle* rect = nullptr;
                        if (blockData[index] != BlockType::air)
                        {
                            const mge::BlockVertexData v(m_chunkPos, {x, y, z});
                            rect = blocksDataSingleton.getBlock(m_chunkSection_p[index]).getTextureRect();


                            int top_block    = y + 1;
                            int bottom_block = y - 1;
                                             
                            int right_block  = x + 1;
                            int left_block   = x - 1;
                                             
                            int back_block   = z + 1;
                            int front_block  = z - 1;


                            bool top_cond    = top_block    <  chunk_y;
                            bool bottom_cond = bottom_block >= 0;

                            bool right_cond  = right_block  <  chunk_x;
                            bool left_cond   = left_block   >= 0;

                            bool back_cond   = back_block   <  chunk_z;
                            bool front_cond  = front_block  >= 0;


                            int top     = top_block    * wzsq + xwz + z;
                            int bottom  = bottom_block * wzsq + xwz + z;

                            int right = y * wzsq + right_block * chunk_z + z;
                            int left    = y * wzsq + left_block  * chunk_z + z;

                            int back    = y * wzsq + xwz + back_block;
                            int front   = y * wzsq + xwz + front_block;

                            if (!(top_cond && m_chunkSection_p[top] != BlockType::air))
                                addFace(v, rect, mge::Face::top, index);

                            if (!(bottom_cond && m_chunkSection_p[bottom] != BlockType::air))
                                addFace( v, rect, mge::Face::bottom, index);

                            if (!(left_cond && m_chunkSection_p[left] != BlockType::air))
                                addFace( v, rect, mge::Face::left, index);
                                
                            if (!(right_cond && m_chunkSection_p[right] != BlockType::air))
                                addFace( v, rect, mge::Face::right, index);
                                
                            if (!(back_cond && m_chunkSection_p[back] != BlockType::air))
                                addFace( v, rect, mge::Face::back, index);

                            if (!(front_cond && m_chunkSection_p[front] != BlockType::air))
                                addFace(v, rect, mge::Face::front, index);
                        }
                    }
            updated = false;
            m_chunkVertexBuffer.InitBuffer(nullptr, mge::chunkMeshesSize, DrawType::DYNAMIC);
            m_chunkIndexBuffer.InitBuffer(nullptr, mge::chunkIndecesCount, DrawType::DYNAMIC);
            //mge::FaceData& fd = faceDataArray_p[0];
            //deleteFace(fd, mge::face::bottom);
            //deleteFace(fd, mge::face::left);
            //deleteFace(fd, mge::face::back);
            deleteBlock({ 0, 55, 0 });
            //deleteBlock({ 0, 0, 0 });
            //deleteBlock({ 0, 0, 0 });
            preRenderUpdate();
            mge::VertexBufferLayout vbl;
            vbl.Push<float>(3);
            vbl.Push<float>(2);
            m_chunkArray.AddBuffer(m_chunkVertexBuffer, vbl);
        }
        void preRenderUpdate()
        {
            if(!updated)
            {
                m_chunkIndexBuffer.Update(m_indeces.data(), m_indeces.size() * sizeof(unsigned int));
                m_chunkVertexBuffer.Update(m_cubes.data(), m_cubes.size() * sizeof(Mesh));
                updated = true;
            }
        }
    };

}

