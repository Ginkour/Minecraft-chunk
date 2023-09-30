#include "Utilities.h"

mge::UINT32 mge::getDrawType(mge::DrawType dt_tp)
{
	switch (dt_tp)
	{
	case mge::DrawType::STATIC:
		return GL_STATIC_DRAW;
		break;
	case mge::DrawType::DYNAMIC:
		return GL_DYNAMIC_DRAW;
		break;
	case mge::DrawType::STRAM:
		return GL_STREAM_DRAW;
		break;
	default:
		return GL_STATIC_DRAW;
		break;
	}
}
void GlClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		logprint("[OpenGL Error] (%i): %s %s: %i", error, function, file, line);
		return false;
	}
	return true;
}
