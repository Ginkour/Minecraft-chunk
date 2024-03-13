#pragma once
#include "Container.h"

#include "Timer.h"
#include "Matrix.h"

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "Rectangle.h"
#include "Text.h"
#include "Vertex.h"
#include "TextRect.h"
#include "Camera.h"
#include <filesystem>
#include <iostream>
#include <filesystem>
#include <chrono>
#include "ChunkMesh.h"
#include <vector>
namespace mge
{
    inline const std::string getInWidth(float number, const unsigned int widthafterdec) 
    {
        std::string str = std::to_string(number);
        return str.substr(0, str.find('.') + widthafterdec + 1);
    }
    enum class MonitorNum : int
    {
        MAIN, SECOND, THIRD
    };
    class OpenGL
    {
    private:
        mge::Vector2f m_size;
        GLFWwindow* window = nullptr;
        float elapsed = 0;
        Timer switchtimer{1.f / 170.f};
        Timer tickTimer{ 1.f / 20.f };
    public:
        bool works()
        {
            return !glfwWindowShouldClose(window);
        };
    private:
        float getSizeByScaleToY(float scale) 
        {
            return (m_size.y * scale);
        }
        float getElaspedTime()
        {
            static double elapsed_time = 0.f;
            static double prev_time = 0.f;
            elapsed_time = glfwGetTime() - prev_time;
            prev_time = glfwGetTime();
            return (float)elapsed_time;
        }
        void PollEvents()
        {
            elapsed = getElaspedTime();
            glfwPollEvents();
        }
        GLFWwindow* CreateWindow(bool fullscr = false, bool native = false, const char* name = "Window", mge::MonitorNum m_num = mge::MonitorNum::MAIN, mge::Vector2u size = { 800, 600 })
        {
            int count;
            GLFWmonitor** handlers = glfwGetMonitors(&count);

            GLFWmonitor* main_handler = nullptr;
            for (int i = 0; i < count; ++i)
            {
                GLFWmonitor* handler = handlers[i];

                // Get monitor properties
                const char* name = glfwGetMonitorName(handler);
                const GLFWvidmode* mode = glfwGetVideoMode(handler);
                if (i == (int)m_num)
                {
                    if (fullscr)
                        main_handler = handler;
                    if (native)
                    {
                        size.x = mode->width;
                        size.y = mode->height;
                    }
                }
                //// Print monitor information
                logprint("\n\nMonitor %i:\n", i);
                logprint(" Name: %s\n", name);
                logprint(" Resolution: %ux%u\n", mode->width, mode->height);
                logprint(" Refresh Rate: %u Hz\n\n", mode->refreshRate);
            }
            glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            //glfwWindowHint(GLFW_SAMPLES, 8);
            // Create a window
            GLFWwindow* window = glfwCreateWindow(size.x, size.y, name, main_handler, nullptr);
            if (!window)
            {
                printf("\nFailed to create GLFW window\n");
                glfwTerminate();
                return nullptr;
            }
            m_size.x = (float)size.x;
            m_size.y = (float)size.y;
            return window;
        }
    public:
        void Run()
        {
            bool flyMode = false;
            mge::Shader d3_triangles("data/shaders/3d/3dtexture.vert", "data/shaders/3d/3dtexture.frag");

            mge::Shader textShader("data/shaders/textRenderer/Text.vert", "data/shaders/textRenderer/Text.frag");

            mge::Texture font("data/fonts/ascii.png");


            mge::Blocks blocks;

            std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
            BlockType* chunkSection = new BlockType[mge::chunkMaxBlocksSize];
            //GENERATE WORLD
            for(unsigned int y = 0; y < chunk_y; ++y)
                for (unsigned int x = 0; x < chunk_x; ++x)
                    for (unsigned int z = 0; z < chunk_z; ++z)
                    {
                        unsigned int index = y * (chunk_x * chunk_z) + x * chunk_z + z;
                        if (y == 0)
                        {
                            chunkSection[index] = BlockType::bedrock;
                        }
                        else if (y == 1)
                        {
                            if (mge::GetRandRangef(0.f, 1.f) > 0.2f) // 80 %
                                chunkSection[index] = BlockType::bedrock;
                            else
                                chunkSection[index] = BlockType::stone;
                        }
                        else if (y == 2)
                        {
                            if (mge::GetRandRangef(0.f, 1.f) > 0.5f) // 50 %
                                chunkSection[index] = BlockType::bedrock;
                            else if (mge::GetRandRangef(0.f, 1.f) > 0.05f) // 95 %
                                chunkSection[index] = BlockType::stone;
                            else
                                chunkSection[index] = BlockType::diamond_ore; //2.5 %
                        }
                        else if (y == 3)
                        {
                            if (mge::GetRandRangef(0.f, 1.f) > 0.8f) // 20 %
                                chunkSection[index] = BlockType::bedrock;
                            else if (mge::GetRandRangef(0.f, 1.f) > 0.05f) // 95 %
                                chunkSection[index] = BlockType::stone;
                            else
                                chunkSection[index] = BlockType::diamond_ore;//4%
                        }
                        else if (y < 50)
                        {
                            if (y < 15 && mge::GetRandRangef(0.f, 1.f) > 0.99f)// 1 %
                            {
                                    chunkSection[index] = BlockType::diamond_ore;
                            }
                            else
                                chunkSection[index] = BlockType::stone;
                        }
                        else if (y == 50)
                        {
                            if (mge::GetRandRangef(0.f, 1.f) > 0.5f) // 50 %
                                chunkSection[index] = BlockType::dirt;
                            else
                                chunkSection[index] = BlockType::stone;
                        }
                        else if (y == 51)
                        {
                            if (mge::GetRandRangef(0.f, 1.f) > 0.2f) // 80 %
                                chunkSection[index] = BlockType::dirt;
                            else
                                chunkSection[index] = BlockType::stone;
                        }
                        else if (y < 55)
                        {
                            chunkSection[index] = BlockType::dirt;
                        }
                        else if (y == 55) 
                        {
                            chunkSection[index] = BlockType::grass;
                        }
                        else if (y == 56  && mge::GetRandRangef(0.f, 1.f) > 0.9f)//10% that 56ths level would get moss cobblestone
                        {
                            chunkSection[index] = BlockType::moss_cobblestone;
                        }
                        //if(x == 1 && y == 1 && z == 1)
                        //    world[index] = BlockType::stone;
                        else 
                        {
                            chunkSection[index] = BlockType::air;
                        }
                    }
            //Generate tree
            chunkSection[56 * (chunk_x * chunk_z) + 9  * chunk_z + 8] = BlockType::oak_log;
            chunkSection[57 * (chunk_x * chunk_z) + 9  * chunk_z + 8] = BlockType::oak_log;
            chunkSection[58 * (chunk_x * chunk_z) + 9  * chunk_z + 8] = BlockType::oak_log;
            chunkSection[59 * (chunk_x * chunk_z) + 9  * chunk_z + 8] = BlockType::oak_log;
            chunkSection[59 * (chunk_x * chunk_z) + 9  * chunk_z + 9] = BlockType::oak_leaves;
            chunkSection[59 * (chunk_x * chunk_z) + 9  * chunk_z + 7] = BlockType::oak_leaves;
            chunkSection[59 * (chunk_x * chunk_z) + 8  * chunk_z + 8] = BlockType::oak_leaves;
            chunkSection[59 * (chunk_x * chunk_z) + 10 * chunk_z + 8] = BlockType::oak_leaves;
            chunkSection[60 * (chunk_x * chunk_z) + 9  * chunk_z + 8] = BlockType::oak_leaves;

            ChunkMesh chunk(chunkSection, { 0, 0 }, blocks);
            
            std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

            std::string chunktime = "Chunk generation time = " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count())+ "ms";

            // SETUP OPENGL RENDERER
            mge::Renderer renderer;
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDepthFunc(GL_LESS);
            glEnable(GL_CULL_FACE);   // Enable face culling
            glCullFace(GL_BACK);      // Cull back-facing polygons
            glFrontFace(GL_CCW);       // Define clockwise as the front face
            glEnable(GL_MULTISAMPLE); 

            //SET SKY COLOR
            renderer.SetClearColor(0.5137f, 0.6431f, 0.8392f, 1.f);


            BlockType rightHand = BlockType::sand;
            //Create IBO
            //IndexBuffer rectangle_ib(indecies, sizeof(indecies) / sizeof(UINT32));
            mge::Mat4 projectionMatrix(MatPreType::IDEN);
            mge::setOrtho(projectionMatrix, 0.f, m_size.x, m_size.y, 0.f, 0.f, 1.f);
            Camera camera(m_size.x, m_size.y, glm::vec3(0.f, 64.f, 0.f), 70.f);
            textShader.Bind();
            textShader.SetUniformMatrix4fv("u_MVP", projectionMatrix);

            const float letter_size = getSizeByScaleToY(0.03f);
            const float offset_size = 100.f;
            
            std::string fpsstr = "FPS: 0";
            std::string frametmstr = "Frametime: 000ms";
            std::string xstr = "x:0.0";
            std::string ystr = "y:0.0";
            std::string zstr = "z:0.0";

            mge::TextString fpsstring(font, textShader, 9, { 10.f,10.f });
            fpsstring.setLetterSize(letter_size);
            fpsstring.setString(fpsstr);
            fpsstring.setTexSlot(0);
            mge::TextString frametmstring(font, textShader, 17, { 10.f, fpsstring.getNextLinePos()});
            frametmstring.setLetterSize(letter_size);
            frametmstring.setString(fpsstr);
            frametmstring.setTexSlot(0);
            const unsigned int coordstrsize = 15;
            mge::TextString xstring(font, textShader, coordstrsize, { 10.f, frametmstring.getNextLinePos() });
            xstring.setLetterSize(letter_size);
            xstring.setString(xstr);
            xstring.setTexSlot(0);
            mge::TextString ystring(font, textShader, coordstrsize, { 10.f, xstring.getNextLinePos() });
            ystring.setLetterSize(letter_size);
            ystring.setString(ystr);
            ystring.setTexSlot(0);
            mge::TextString zstring(font, textShader, coordstrsize, { 10.f, ystring.getNextLinePos() });
            zstring.setLetterSize(letter_size);
            zstring.setString(zstr);
            zstring.setTexSlot(0);
            mge::TextString chunktmstr(font, textShader, chunktime.size(), {10.f, zstring.getNextLinePos()});
            chunktmstr.setLetterSize(letter_size);
            chunktmstr.setString(chunktime);
            chunktmstr.setTexSlot(0);

            float rotate_speed = 1.2f;
            float rotate_frame_speed = 0.f;
            float speed = 6.f;
            float frame_speed = 0.f;
            while (works())
            {
                renderer.Clear();
                PollEvents();
                tickTimer.incBy(elapsed);
                static unsigned int tick = 0;
                static int fire_frame = 15;
                if (tickTimer.isOver())
                {
                    ++fire_frame;
                    ++tick;
                    if (tick > 19)
                        tick = 0;

                    if (tick == 19)
                    {
                        int fps = (int)(1.f / elapsed);
                        fpsstr = "FPS: " + std::to_string(fps);
                        frametmstr = "Frametime: " + getInWidth(elapsed * 1000, 2) + "ms";
                        fpsstring.setString(fpsstr);
                        frametmstring.setString(frametmstr);
                    }
                    xstr = "x:" + getInWidth(camera.m_position.x, 2);
                    ystr = "y:" + getInWidth(camera.m_position.y, 2);
                    zstr = "z:" + getInWidth(camera.m_position.z, 2);

                    xstring.setString(xstr);
                    ystring.setString(ystr);
                    zstring.setString(zstr);
                    float fpx = camera.m_position.x;
                    float fpy = camera.m_position.y;
                    float fpz = camera.m_position.z;

                    int px = (int)fpx;
                    int py = (int)fpy;
                    int pz = (int)fpz;
                    mge::Vector3i ppos = { px, py, pz };
                    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
                        rightHand = BlockType::stone;
                    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
                        rightHand = BlockType::dirt;
                    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
                        rightHand = BlockType::grass;
                    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
                        rightHand = BlockType::cobblestone;
                    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
                        rightHand = BlockType::moss_cobblestone;
                    if (camera.MOUSE_L)
                    {
                        chunk.deleteBlock({ px, py, pz });
                    }
                    if (camera.MOUSE_R)
                    {
                        chunk.addBlock({ px, py, pz }, rightHand);
                    }
                }
                rotate_frame_speed = rotate_speed * elapsed;

                frame_speed = speed * elapsed;
                camera.Inputs(window, elapsed, 0.1f, 10000.f);

                camera.Matrix(d3_triangles, "u_MVP");
                blocks.terrainAtlas->Bind();


                // Clear Z buffer
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST); 

                chunk.preRenderUpdate();
                renderer.Draw(chunk.m_chunkArray, chunk.m_chunkIndexBuffer, d3_triangles, chunk.m_indeces.size());

                // Turn off Z buffer for text Rendering
                glDisable(GL_DEPTH_TEST);

                renderer.Draw(fpsstring);
                renderer.Draw(frametmstring);
                renderer.Draw(xstring);
                renderer.Draw(ystring);
                renderer.Draw(zstring);
                renderer.Draw(chunktmstr);

                renderer.Display(window);
            }
            delete[]chunkSection;
        };
        OpenGL()
        {
            // Initialize GLFW
            if (!glfwInit())
            {
                logprint("\nGLFW init error!\n");
                exit(-1);
            }
            // Set up the OpenGL context
            window = CreateWindow(false, false, "Minecraft Chunk", MonitorNum::MAIN, mge::Vector2u(1600, 900));

            glfwMakeContextCurrent(window); 

            //Turn off VSynch
            glfwSwapInterval(0);
            if (glewInit() != GLEW_OK)
            {
                logprint("\nGLEW init error!\n");
                exit(-1);
            }
            logprint("OpenGL version: %s\n", (char*)glGetString(GL_VERSION));


            // Load icon image(s)
            int width, height, channels;
            unsigned char* iconPixels = stbi_load("icon.png", &width, &height, &channels, 0);

            GLFWimage iconImage;
            iconImage.width = width;
            iconImage.height = height;
            iconImage.pixels = iconPixels;

            // Set the window icon
            glfwSetWindowIcon(window, 1, &iconImage);

            //Print debug information
            GLint max;
            glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &max);
            logprint("\nGL_MAX_VERTEX_TEXTURE_IMAGE_UNITS = %i\n", max);
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max);
            logprint("\nGL_MAX_COMBINED_TEXTURE_IMAGE_UNITS = %i\n", max);
            glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &max);
            logprint("\nGL_MAX_ELEMENTS_VERTICES = %i\n", max);
            glGetIntegerv(GL_MAX_ELEMENTS_INDICES, &max);
            logprint("\nGL_MAX_ELEMENTS_INDICES = %i\n", max);
            free(iconPixels);

        }
        ~OpenGL()
        {
            glfwTerminate();
        }
    };
}

