#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"


#include "typedefs.h"
#include "Container.h"
#include <thread>
#include <chrono>


#ifdef _CONSOLE
#include <cstdlib>
#include <stdio.h>
#define logprint(...) printf(__VA_ARGS__)
#else
#define logprint(x)
#endif


#define ASSERT(x)  if(!(x)) __debugbreak();
#define GLCall(x) GlClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))
namespace mge 
{
    enum class DrawType
    {
        STATIC,
        DYNAMIC,
        STRAM,
    };
    struct uIntRect
    {
        unsigned int left, top, width, height;
        uIntRect(unsigned int _left, unsigned int _top, unsigned int _width, unsigned int _height) : left(_left), top(_top), width(_width), height(_height) {};
    };
    inline float Absf(float value)
    {
        unsigned int* val = (unsigned int*)&value;
        *val &= 0x7FFFFFFF;
        return value;
    }
    mge::UINT32 getDrawType(mge::DrawType dt_tp);
}
void GlClearError();
bool GLLogCall(const char* function, const char* file, int line);