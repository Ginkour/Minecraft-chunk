#pragma once
#include "Utilities.h"
#include "string"
namespace mge 
{
	class Texture
	{
	private:
		INT32 m_Width, m_Height, m_BPP;
		UINT32 m_RendererID;
		UINT8* m_LocalBuffer;
		std::string m_FilePath;
	public:
		Texture(const std::string& filepath, bool smooth = false, bool repeat = false, bool mipmap = false);
		~Texture();
	public:
		void Bind(UINT32 slot = 0);
		void Unbind();
		inline const INT32 getWidth() const { return m_Width; }
		inline const INT32 getHeight() const { return m_Height; }
		inline const INT32 getBPP() const { return m_BPP; }

	};
}

