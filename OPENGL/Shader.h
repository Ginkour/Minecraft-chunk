#pragma once
#include "Utilities.h"
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>


#include "Matrix.h"
#include "Container.h"

namespace mge 
{
    class Shader
    {
    private:
        UINT32 m_ShaderID;
        std::unordered_map<std::string, INT32> m_UniformLocationCache;
        static mge::UINT32 currentShader;
    public:
        Shader(const char* const vsf, const char* const fsf, const char* const gsf = nullptr, const char* const tcsf = nullptr, const char* const tesf = nullptr);
        ~Shader();
        void Bind() const;
        void Unbind() const;
        void SetUniform1i(const char* const name, int v0);
        void SetUniform1f(const char* const name, float v0);
        void SetUniform3f(const char* const name, float v0, float v1, float v2);
        void SetUniform4f(const char* const name, float v0, float v1, float v2, float v3); 
        void SetUniformMatrix4fv(const char* const name, const glm::mat4& matrix);
        void SetUniformMatrix4fv(const char* const name, const mge::Mat4& matrix);
        void SetUniformMatrix4fv(INT32 i, const mge::Mat4& matrix);
        const INT32 GetUniformLocation(const char* const name);
    private:
        UINT32 CompileShader(UINT32 type, const char* const source);
    };
}

