#pragma once
#include "Utilities.h"
#include "Rectangle.h"
#include "TextRect.h"
namespace mge 
{
    enum class LetterType : char
    {
        NONE = 0,
        SPACE = 1,
        TAB = 2,
        NEWL = 3,
    };

    constexpr float p10_8 = 10.f / 8.f;
    constexpr float p9_8 = 9.f / 8.f;
    constexpr float p7_8 = 7.f / 8.f;
    constexpr float p6_8 = 6.f / 8.f;
    constexpr float p5_8 = 5.f / 8.f;
    constexpr float p4_8 = 4.f / 8.f;
    constexpr float p3_8 = 3.f / 8.f;
    constexpr float p2_8 = 2.f / 8.f;
    constexpr float p1_8 = 1.f / 8.f;
    constexpr unsigned int atlas_size = 16;
    struct QuadIndeces
    {
        unsigned int m_indeces[6];
    };
    class TextString 
    {
    private:
        mge::Quad* m_quads_p;
        mge::QuadIndeces* m_indeces_p;
        mge::TransformCPU* m_transforms_p;
        mge::Shader* m_shader_p;
        mge::Texture* m_texture_p;


        unsigned int m_max_str_size;
        // the actual size is 1 bigger, this value represents the last position of quad in quad array
        unsigned int m_str_size;

        bool wholeupdate;
        mge::Vector2f offset;
        mge::Vector2f newLineOffset;
        float m_letter_size;
        float interline_space;
        float maxPos;
        float spaceSize;
        unsigned int pixel_per_letter;
        bool box;
        std::string m_string;

        mge::VertexArray VA;
        mge::VertexBuffer VB;
        mge::IndexBuffer IB;
        mge::Vector2f m_position;
        mge::Vector4f m_color;
    public:
        void setPosition(mge::Vector2f newpos)
        {
            if (m_str_size > 0)
                move(newpos);
            m_position = newpos;
        }
        void setLetterSize(float size)
        {
            m_letter_size = size;
            float lineoffset = m_letter_size * p1_8;
            spaceSize = m_letter_size * p6_8;
            newLineOffset = { lineoffset , lineoffset };
            wholeupdate = true;
            if (m_str_size > 0)
                setString(m_string);
        }

        unsigned int wordLength(std::string& string, unsigned int current_pos)
        {
            if (current_pos >= string.size())
                return 0;
            if (string.at(current_pos) == ' ')
                return 0;
            unsigned int length = 0;
            for (unsigned int i = current_pos; i < string.size(); ++i)
            {
                if (string.at(i) != ' ')
                    ++length;
                else return length;
            }
            return length;
        };
        const float getNextLinePos() const
        {
            return m_position.y + m_letter_size * p10_8;
        }
        void setletter(mge::Quad& quad, char letter, float letter_size)
        {
            mge::Vector2u atlas_pos_2d;
            atlas_pos_2d.x = letter % atlas_size;
            atlas_pos_2d.y = ((letter - atlas_pos_2d.x) / atlas_size);
            uIntRect m_rect{ atlas_pos_2d.x * pixel_per_letter, atlas_pos_2d.y * pixel_per_letter, pixel_per_letter, pixel_per_letter };
            mge::setTextRectTextureRect(quad, &m_rect, *m_texture_p);
            // 1 pixels
            if (letter == '!' || letter == '\'' || letter == ',' || letter == '.' || letter == ':' || letter == ';' || letter == '|' || letter == 'i')
                letter_size *= p2_8;
            // 2 pixels
            else if (letter == '`' || letter == 'l')
                letter_size *= p3_8;
            // 3 pixels
            else if (letter == 'I' || letter == 't' || letter == '{' || letter == '}' || letter == '[' || letter == ']' || letter == '(' || letter == ')' || letter == '*')
                letter_size *= p4_8;
            // 4 pixels
            else if (letter == 'f' || letter == 'k')
                letter_size *= p5_8;
            // 6 pixels
            else if (letter == '~')
                letter_size *= p7_8;
            // 5 pixels
            else
                letter_size *= p6_8;
            offset.x += letter_size;
        }
        void setString(std::string& string)
        {
            m_string = string; 
            //setLetterSize(m_letter_size);
            wholeupdate = true;
            offset = newLineOffset;
            // shadow rect
            updateIndeces(0);
            m_transforms_p[0].setPosition(m_position);
            mge::setTextRectColor(m_quads_p[0], {0.6f, 0.6f, 0.6f, 0.6f});
            mge::setTextRectTextureSlot(m_quads_p[0], -1.f);
            // end shadow rect
            m_str_size = 1; // 0 is allocated for shadow  
            float currentWordLength;
            for (size_t i = 0; i < string.size(); i++)
            {
                LetterType lett_t;
                switch (string.at(i))
                {
                case' ':
                    lett_t = LetterType::SPACE;
                    offset.x += spaceSize;
                    break;
                case'\n':
                    lett_t = LetterType::NEWL;
                    break;
                case'\t':
                    lett_t = LetterType::TAB;
                    offset.x += spaceSize * 4;
                    break;
                default:
                    lett_t = LetterType::NONE;
                    break;
                }
                if ((bool)lett_t)
                {
                    if (box)
                    {
                        currentWordLength = spaceSize * wordLength(string, (mge::UINT32)(i + 1));
                        if (lett_t == LetterType::NEWL || m_position.x + offset.x + currentWordLength >= maxPos)
                        {
                            offset.y += m_letter_size + interline_space;
                            offset.x = newLineOffset.x;
                        }
                    }
                }
                else
                {
                    if (m_str_size < m_max_str_size)
                    {
                        updateIndeces(m_str_size);
                        mge::setTextRectSize(m_quads_p[m_str_size], m_letter_size);
                        m_transforms_p[m_str_size].setPosition(m_position + offset);
                        setletter(m_quads_p[m_str_size], string.at(i), m_letter_size);
                        mge::setTextRectColor(m_quads_p[m_str_size], m_color);
                        ++m_str_size;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            --m_str_size;
            mge::setTextRectSize(m_quads_p[0], offset.x, m_letter_size * p9_8);
            return;
        }
        void updateIndeces(const unsigned int pos)
        {
            unsigned int indexoffset = 4 * pos;
            m_indeces_p[pos].m_indeces[0] = 0 + indexoffset;
            m_indeces_p[pos].m_indeces[1] = 1 + indexoffset;
            m_indeces_p[pos].m_indeces[2] = 2 + indexoffset;
            m_indeces_p[pos].m_indeces[3] = 2 + indexoffset;
            m_indeces_p[pos].m_indeces[4] = 3 + indexoffset;
            m_indeces_p[pos].m_indeces[5] = 0 + indexoffset;
        }
        void setTexSlot(const int slot)
        {
            for (size_t i = 1; i < m_max_str_size; i++)
            {
                mge::setTextRectTextureSlot(m_quads_p[i], slot);
            }
        }
        void setColor(mge::Vector4f color)
        {
            m_color = color;
        }
        inline const unsigned int getSizeBytesOfQuads() const
        {
            return sizeof(Quad) * (m_str_size + 1);
        }
        inline const unsigned int getSizeBytesOfIndeces() const
        {
            return sizeof(QuadIndeces) * (m_str_size + 1);
        }
        void checkUpdates() 
        {
            if (wholeupdate)
            {
                for (unsigned int i = 0; i <= m_str_size; ++i)
                {
                    mge::TextRectTransform(m_quads_p[i],m_transforms_p[i]);
                }
                VB.Update(m_quads_p, getSizeBytesOfQuads());
                IB.Update((mge::UINT32*)m_indeces_p, getSizeBytesOfIndeces());

                wholeupdate = false;
            }
        }
    private:
        void updateColor() 
        {
            for (unsigned int i = 1; i <= m_str_size; ++i)
            {
                mge::setTextRectColor(m_quads_p[i], m_color);
            }
            wholeupdate = true;
        }
        void move(mge::Vector2f newpos)
        {
            newpos -= m_position;
            for (unsigned int i = 0; i <= m_str_size; ++i)
            {
                m_transforms_p[i].move(newpos);
            }
            wholeupdate = true;
        }
    public:
        TextString(mge::Texture& texture, mge::Shader& shader, const unsigned int maxSize, mge::Vector2f pos, bool _box = false, float intrl_spc = 0.f, float boxSize = 200.f) :
            m_texture_p(&texture),
            m_shader_p(&shader),
            m_max_str_size(maxSize + 1), // one rectangle for shadow rect
            m_str_size(0),
            m_position(pos),
            VB(nullptr, sizeof(mge::Quad)* m_max_str_size, mge::DrawType::DYNAMIC),
            IB(nullptr, 6 * m_max_str_size),
            wholeupdate(0), offset(0.f, 0.f),
            interline_space(intrl_spc - p1_8),
            m_letter_size(10.f),
            maxPos(pos.x + boxSize),
            pixel_per_letter(m_texture_p->getHeight() / atlas_size), 
            m_color(1.f, 1.f, 1.f, 1.f),
            box(_box)
        {
            m_quads_p = new Quad[m_max_str_size];
            m_indeces_p = new QuadIndeces[m_max_str_size];
            m_transforms_p = new TransformCPU[m_max_str_size];

            mge::VertexBufferLayout layout;
            layout.Push<float>(3);
            layout.Push<float>(4);
            layout.Push<float>(2);
            layout.Push<float>(1);
            VA.AddBuffer(VB, layout);
        }
        ~TextString()
        {
            delete[] m_quads_p;
            delete[] m_indeces_p;
            delete[] m_transforms_p;
        }
        friend class Renderer;
    };
}

