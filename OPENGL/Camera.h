#pragma once
#include "Utilities.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/rotate_vector.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "Shader.h"
class Camera
{
public:
	glm::vec3 m_position;
	glm::vec3 m_orientation = glm::vec3(0.f, 0.f, -1.f);
	glm::vec3 up_vec = glm::vec3(0.f, 1.f, 0.f);
	glm::mat4 projection;
	glm::mat4 view = glm::mat4(1.f);
	float m_a_ratio;
	float width;
	float height;
	float speed = 2.5f;
	float sensetivity = 100.f;
	float run_mult = 2.f;
	float constFOV = glm::radians(70.f);
	float fovMult = 1.f;
	float maxfov = 1.15f;
	bool MOUSE_CAPTURED = false; 
	bool ACTIVE_INTERFACE = false;
	bool D = false;
	bool A = false;
	bool S = false;
	bool W = false;
	bool LSHIFT = false;
	bool SPACE = false;
	bool LCTRL = false;
	bool R = false;
	bool ESC =false;
				
	bool UP = 	false;
	bool DOWN = 	false;
	bool LEFT = 	false;
	bool RIGHT =	false;
	bool MOUSE_L =	false;
	bool MOUSE_R =	false;
	bool MOUSE_L_RL = false;
	bool MOUSE_R_RL = false;
	Camera(float width, float height, glm::vec3 position, float fov):
		m_a_ratio(width / height), width(width), height(height), m_position(position), constFOV(glm::radians(fov))
	{
	}
	void setProjection(float nearPlane, float farPlane) 
	{
		projection = glm::perspective(constFOV * fovMult, m_a_ratio, nearPlane, farPlane);
	}
	void Matrix(mge::Shader& shader, const char* uniform)
	{
		view = glm::lookAt(m_position, m_position + m_orientation, up_vec);
		shader.Bind();
		shader.SetUniformMatrix4fv(uniform, projection * view);
	}
	void Inputs(GLFWwindow* window, float elapsed, float nearPlane, float farPlane)
	{
		 D		= glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
		 A		= glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
		 S		= glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
		 W		= glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;

		 LSHIFT = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS;
		 SPACE	= glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
		 LCTRL	= glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS;

		 R		= glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS;
		 ESC	= glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;

		 UP = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
		 DOWN = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
		 LEFT = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
		 RIGHT = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS; 

		 MOUSE_L = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS;
		 MOUSE_L_RL = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE;
		 MOUSE_R = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS;
		 MOUSE_R_RL = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE;;
		float frame_speed;
		float fovspeed = elapsed;
		if (LCTRL && W)
		{
			frame_speed = speed * run_mult * elapsed;
			if (fovMult < maxfov)
				fovMult += fovspeed;
			if (fovMult > maxfov)
				fovMult = maxfov;
			setProjection(nearPlane, farPlane);
		}
		else
		{
			frame_speed = speed * elapsed;
			if(fovMult > 1.f)
				fovMult -= fovspeed;
			else if(fovMult < 1.f)
				fovMult = 1.f;
			setProjection(nearPlane, farPlane);
		}
		if (W)
		{
			m_position += frame_speed * m_orientation;
		}
		if (A)
		{
			m_position += frame_speed * -glm::normalize(glm::cross(m_orientation, up_vec));
		}
		if (S)
		{
			m_position += frame_speed * -m_orientation;
		}
		if (D)
		{
			m_position += frame_speed * glm::normalize(glm::cross(m_orientation, up_vec));
		}
		if (SPACE)
		{
			m_position += frame_speed * up_vec;
		}
		if (LSHIFT)
		{
			m_position += frame_speed * -up_vec;
		}
		if (ESC)
		{
			MOUSE_CAPTURED = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		if (!MOUSE_CAPTURED)
		{
			if (MOUSE_L)
			{
				MOUSE_CAPTURED = true; 
				glfwSetCursorPos(window, width / 2, height / 2);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
		}
		
		if(!glfwGetWindowAttrib(window, GLFW_HOVERED) || ESC || ACTIVE_INTERFACE)
		{
			MOUSE_CAPTURED = false;
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
		else if(!MOUSE_CAPTURED)
		{
			if (MOUSE_L)
			{
				MOUSE_CAPTURED = true;
				glfwSetCursorPos(window, width / 2, height / 2);
				glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			}
		}
		else
		{
			double xpos, ypos;
			glfwGetCursorPos(window, &xpos, &ypos);

			float rotX = sensetivity * ((float)xpos - width / 2) / width;
			float rotY = sensetivity * ((float)ypos - height / 2) / height;

			//glm::vec3 newOrient
			glfwSetCursorPos(window, width * 0.5f, height * 0.5f);
			m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), glm::normalize(glm::cross(m_orientation, up_vec)));
			m_orientation = glm::rotate(m_orientation, glm::radians(-rotX), up_vec);
		}
	}
};

