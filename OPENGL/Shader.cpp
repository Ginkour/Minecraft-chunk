#include "Shader.h"

const size_t shaderSize = 5;
mge::UINT32 mge::Shader::currentShader = 0;
unsigned int shaderUintCode[shaderSize] =
{
    GL_VERTEX_SHADER,
    GL_FRAGMENT_SHADER,
    GL_GEOMETRY_SHADER,
    GL_TESS_CONTROL_SHADER,
    GL_TESS_EVALUATION_SHADER
};
namespace mge
{
    Shader::Shader(const char* const vsf, const char* const fsf, const char* const gsf, const char* const tcsf, const char* const tesf)
        :m_ShaderID(0)
    {
        const char* files_paths[shaderSize] = { nullptr };
        mge::UINT32 programs[shaderSize] = { 0 };
        std::ifstream file;
        
        files_paths[0] = vsf;
        files_paths[1] = fsf;
        files_paths[2] = gsf;
        files_paths[3] = tcsf;
        files_paths[4] = tesf;

        m_ShaderID = glCreateProgram();
        logprint("\nCreating shader programm with ID:\"%i\"\n", m_ShaderID);
        for (size_t i = 0; i < shaderSize; i++)
        {
            if (files_paths[i])
            {
                file.open(files_paths[i]);
                if (file.is_open())
                {
                    std::string line;
                    std::stringstream shaderstream;
                    while (getline(file, line))
                    {
                        shaderstream << line << '\n';
                    }
                    programs[i] = CompileShader(shaderUintCode[i], shaderstream.str().c_str());
                    glAttachShader(m_ShaderID, programs[i]);
                    logprint("Shader file:\"%s\", read succesfully!\n", files_paths[i]);
                }
                else 
                {
                    logprint("Shader file: \"%s\", loading error!\n", files_paths[i]);
                    glDeleteProgram(m_ShaderID);
                    exit(0);
                }
                file.close();
            }
        }
        int succes;
        glLinkProgram(m_ShaderID);
        glGetProgramiv(m_ShaderID, GL_LINK_STATUS, &succes);
        if (succes)
        {
            logprint("Linking succesfull\n");
        }
        else 
        {
            logprint("Linking Error!\n");
        }
        glValidateProgram(m_ShaderID);
        glGetProgramiv(m_ShaderID, GL_VALIDATE_STATUS, &succes);
        if (succes)
        {
            logprint("Validation succesfull\n\n");
        }
        else
        {
            logprint("Validating Error!\n\n");
        }
        for (size_t i = 0; i < shaderSize; i++)
        {
            if(programs[i])
                glDeleteShader(programs[i]);
        }
    }
    Shader::~Shader()
    {
        glDeleteProgram(m_ShaderID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_ShaderID);
    }

    void Shader::Unbind() const
    {
        glUseProgram(0);
    }
    void Shader::SetUniform1i(const char* const name, int v0)
    {
        glUniform1i(GetUniformLocation(name), v0);
    }
    void Shader::SetUniform1f(const char* const name, float v0)
    {
        glUniform1f(GetUniformLocation(name), v0);
    }
    void Shader::SetUniform3f(const char* const name, float v0, float v1, float v2)
    {
        glUniform3f(GetUniformLocation(name), v0, v1, v2);
    }
    void Shader::SetUniform4f(const char* const name, float v0, float v1, float v2, float v3)
    {
        glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
    }
    void Shader::SetUniformMatrix4fv(const char* const name, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
    }
    void Shader::SetUniformMatrix4fv(const char* const name, const mge::Mat4& matrix)
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix.m_mat[0][0]);
    }
    void Shader::SetUniformMatrix4fv(INT32 i, const mge::Mat4& matrix)
    {
        glUniformMatrix4fv(i, 1, GL_FALSE, &matrix.m_mat[0][0]);
    }
    const INT32 Shader::GetUniformLocation(const char* const name)
    {
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
            return m_UniformLocationCache[name];
        else
        {
            INT32 location = glGetUniformLocation(m_ShaderID, name);
            if (location == -1)
            {
                logprint("Warning: uniform %s, %i: doesn't exist\n", name, glGetError());
            }
            else
            {
                logprint("Uniform %s, added to map at shader program %i, at location %i\n", name, m_ShaderID, location);
                m_UniformLocationCache[name] = location;
            }
            return location;
        }
    }

    UINT32 Shader::CompileShader(UINT32 type, const char* const source)
    {
        UINT32 id = glCreateShader(type);
        glShaderSource(id, 1, &source, nullptr);
        glCompileShader(id); 
        //GLenum code = glGetError();
        //if(code != GLEW_OK)
        //    logprint("GL error: %i\n", code);
        INT32 result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            INT32 length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            //stack allocation of char array on the stack
            //char* message = (char*)alloca(length * sizeof(char));
            char* message = (char*)_malloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            logprint("\n Failed to compile %s shader: %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
            glDeleteShader(id);
            return 0;
        }
        return id;
    }
}