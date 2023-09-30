#pragma once
#include "Utilities.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Rectangle.h"
#include "Text.h"
namespace mge 
{
	class Renderer
	{
	private:

	public:
		Renderer();
		~Renderer();
	public:
		void SetClearColor(float r, float g, float b, float a);
		void Clear();
		void Draw(mge::TextString& textstr);
		void Draw(mge::Rectangle& rect);
		void Draw(const VertexArray& va, const IndexBuffer& ib,
			const Shader& shader, const unsigned int count) const;
		void Draw(const VertexArray& va, const Shader& shader,
			const unsigned int count) const;
		void Display(GLFWwindow* window);
	};

}
