#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
namespace mge 
{
    
    
    // the number of rectangular face in cube

    constexpr int face_size = 6;
    constexpr int indeces_size = face_size * 2/*triangles*/ * 3/*vertices*/;
    class Cube
    {

    public:

        bool bottom = false;
        bool top = false;
        bool left = false;
        bool right = false;
        bool back = false;
        bool front = false;
        unsigned int drawable_size;

        Mesh meshes[face_size];
        unsigned int indeces[indeces_size];
        mge::VertexArray VA;
        mge::VertexBuffer VB;
        mge::IndexBuffer IB;
        void setFace(size_t& i, unsigned int& k)
        {
            indeces[i] = k;
            indeces[i + 1] = k + 1;
            indeces[i + 2] = k + 2;
            indeces[i + 3] = k;
            indeces[i + 4] = k + 2;
            indeces[i + 5] = k + 3;
            i += 6;
        }
        void setFaces()
        {
            // INITILIZE INDEX BUFFER
            size_t i = 0;
            unsigned int k = 0;
            for (size_t m = 0; m < 6; ++m)
            {
                switch (m)
                {
                case 0:
                    // bottom face
                    if (bottom)
                        setFace(i, k);
                    break;
                case 1:
                    // top face
                    if (top)
                        setFace(i, k);
                    break;
                case 2:
                    // left face
                    if (left)
                        setFace(i, k);
                    break;
                case 3:
                    // right face
                    if (right)
                        setFace(i, k);
                    break;
                case 4:
                    // back face
                    if (back)
                        setFace(i, k);
                    break;
                case 5:
                    // front face
                    if (front)
                        setFace(i, k);
                    break;
                }
                k += 4;
            }
            drawable_size = i;
            IB.Update(indeces, sizeof(mge::UINT32) * i);
        }
        Cube(mge::TextureRectangle* tr, mge::Vector3f pos, bool invisible = true)
        {
            // Base vertices (counter-clockwise order)
            // bottom face
            /*0 */ meshes[0].m_vert[0].pos = v[3], meshes[0].m_vert[0].texCoord = tr[0].t00;
            /*1 */ meshes[0].m_vert[1].pos = v[0]; meshes[0].m_vert[1].texCoord = tr[0].t01;
            /*2 */ meshes[0].m_vert[2].pos = v[1]; meshes[0].m_vert[2].texCoord = tr[0].t11;
            /*3 */ meshes[0].m_vert[3].pos = v[2]; meshes[0].m_vert[3].texCoord = tr[0].t10;
            // top face
            /*4 */ meshes[1].m_vert[0].pos = v[4]; meshes[1].m_vert[0].texCoord = tr[2].t00;
            /*5 */ meshes[1].m_vert[1].pos = v[7]; meshes[1].m_vert[1].texCoord = tr[2].t01;
            /*6 */ meshes[1].m_vert[2].pos = v[6]; meshes[1].m_vert[2].texCoord = tr[2].t11;
            /*7 */ meshes[1].m_vert[3].pos = v[5]; meshes[1].m_vert[3].texCoord = tr[2].t10;
            // left face
            /*8 */ meshes[2].m_vert[0].pos = v[3]; meshes[2].m_vert[0].texCoord = tr[1].t00;
            /*9 */ meshes[2].m_vert[1].pos = v[7]; meshes[2].m_vert[1].texCoord = tr[1].t01;
            /*10*/ meshes[2].m_vert[2].pos = v[4]; meshes[2].m_vert[2].texCoord = tr[1].t11;
            /*11*/ meshes[2].m_vert[3].pos = v[0]; meshes[2].m_vert[3].texCoord = tr[1].t10;
            // right face
            /*12*/ meshes[3].m_vert[0].pos = v[1]; meshes[3].m_vert[0].texCoord = tr[1].t00;
            /*13*/ meshes[3].m_vert[1].pos = v[5]; meshes[3].m_vert[1].texCoord = tr[1].t01;
            /*14*/ meshes[3].m_vert[2].pos = v[6]; meshes[3].m_vert[2].texCoord = tr[1].t11;
            /*15*/ meshes[3].m_vert[3].pos = v[2]; meshes[3].m_vert[3].texCoord = tr[1].t10;
            // back face
            /*16*/ meshes[4].m_vert[0].pos = v[2]; meshes[4].m_vert[0].texCoord = tr[1].t00;
            /*17*/ meshes[4].m_vert[1].pos = v[6]; meshes[4].m_vert[1].texCoord = tr[1].t01;
            /*18*/ meshes[4].m_vert[2].pos = v[7]; meshes[4].m_vert[2].texCoord = tr[1].t11;
            /*19*/ meshes[4].m_vert[3].pos = v[3]; meshes[4].m_vert[3].texCoord = tr[1].t10;
            // front face
            /*20*/ meshes[5].m_vert[0].pos = v[0]; meshes[5].m_vert[0].texCoord = tr[1].t00;
            /*21*/ meshes[5].m_vert[1].pos = v[4]; meshes[5].m_vert[1].texCoord = tr[1].t01;
            /*22*/ meshes[5].m_vert[2].pos = v[5]; meshes[5].m_vert[2].texCoord = tr[1].t11;
            /*23*/ meshes[5].m_vert[3].pos = v[1]; meshes[5].m_vert[3].texCoord = tr[1].t10;
            // ...
            VB.InitBuffer(meshes, sizeof(meshes), DrawType::STATIC);
            IB.InitBuffer(nullptr, indeces_size, DrawType::DYNAMIC);
            setFaces();
            mge::VertexBufferLayout vbl;
            vbl.Push<float>(3);
            vbl.Push<float>(2);
            VA.AddBuffer(VB, vbl);
        }

    };
}
class Mesh
{
};

