#pragma once
#include "Matrix.h"
#include "Shader.h"
namespace mge
{
	class Camera2D
	{
	private:
		mge::INT32 m_proj_id;
		// has its own constructor
		mge::Mat4 projection;
		mge::Transform transform;
		mge::Shader* m_sh;
	public:
		Camera2D(mge::Shader* sh, mge::Vector2f& screen) : m_sh(sh)
		{
			if(!sh)
				throw std::runtime_error("shader can't be null");
			m_proj_id = sh->GetUniformLocation("u_MVP");
		};
		const void setSize(mge::Vector2f& screen, mge::Shader* sh = nullptr)
		{
			mge::setOrtho(projection, 0.f, screen.x, screen.y, 0.f, -1.f, 1.f);
			if (!sh || sh == m_sh)
			{
				// Update Model View Projection uniform
				m_sh->SetUniformMatrix4fv(m_proj_id, projection);
			}
			else 
			{
				sh->Bind();
				// Update Model View Projection uniform
				m_sh->SetUniformMatrix4fv("u_MVP", projection);
				sh->Unbind();
			}
		}
	};
}

