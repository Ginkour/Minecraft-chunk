#include "Renderer.h"


namespace mge
{
	Renderer::Renderer()
	{
	}

	Renderer::~Renderer()
	{
	}
	void Renderer::SetClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}
	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Renderer::Draw(mge::TextString& textstr)
	{
		textstr.checkUpdates();

		textstr.VA.Bind();
		textstr.m_shader_p->Bind();
		textstr.m_texture_p->Bind(0);
		textstr.IB.Bind();
		GLCall(glDrawElements(GL_TRIANGLES, 6 * (textstr.m_str_size + 1), GL_UNSIGNED_INT, nullptr));
	}
	void Renderer::Draw(mge::Rectangle& rect)
	{
		rect.va.Bind();

		rect.m_shader_p->Bind();
		if (!rect.bufferUpdated)
		{
			rect.m_vb.Update(rect.vertices, rect.m_vb.getSize());
			rect.bufferUpdated = true;
		}
		rect.m_ib_p->Bind();
		rect.m_texture_p->Bind(0);
		rect.m_shader_p->SetUniform1i("u_Texture", 0);
		rect.m_shader_p->SetUniformMatrix4fv("u_T", rect.transf.m_transfrom);
		rect.m_shader_p->SetUniform4f("u_C", rect.color.x, rect.color.y, rect.color.z, rect.color.t );
		GLCall(glDrawElements(GL_TRIANGLES, rect.m_ib_p->GetCount(), GL_UNSIGNED_INT, nullptr));
	}
	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, const unsigned int count) const
	{
		if (count > 0)
		{
			shader.Bind();
			va.Bind();
			ib.Bind();
			GLCall(glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr));
		}
	}
	void Renderer::Draw(const VertexArray& va, const Shader& shader, const unsigned int count) const
	{
		if (count > 0)
		{
			va.Bind();
			shader.Bind();
			GLCall(glDrawArrays(GL_TRIANGLE_STRIP, 0, count / 3));
		}
	}
	void Renderer::Display(GLFWwindow* window)
	{
		glfwSwapBuffers(window);
	}
}