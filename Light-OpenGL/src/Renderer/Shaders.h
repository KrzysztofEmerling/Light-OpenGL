#pragma once
#include "Macros.h"
#include <unordered_map>
#include <string>

enum ShaderType
{
    UNKNOWN = -1,
    VERTEX = 0,
    FRAGMENT = 1,
    GEOMETRY = 2,
    TESSELLATION_CONTROL = 3,
    TESSELLATION_EVALUATION = 4,
    COMPUTE = 5
};
struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
    std::string GeometrySource;
    std::string TessellationControlSource;
    std::string TessellationEvaluationSource;
    std::string ComputeSource;
};

namespace Graphics
{
    class Shader
    {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        std::unordered_map<std::string, int> m_Uniforms;
    public:
        Shader(const std::string& filepath);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void SetSampler(const std::string& uniform_name, const unsigned int count,const int* value);

        void SetUniform1f(const std::string& uniform_name, const float& value);
        void SetUniform2f(const std::string& uniform_name, const glm::vec2& value);
        void SetUniform3f(const std::string& uniform_name, const glm::vec3& value);
        void SetUniform4f(const std::string& uniform_name, const glm::vec4& value);

        void SetUniform1i(const std::string& uniform_name, const int& value);
        void SetUniform2i(const std::string& uniform_name, const glm::ivec2& value);
        void SetUniform3i(const std::string& uniform_name, const glm::ivec3& value);
        void SetUniform4i(const std::string& uniform_name, const glm::ivec4& value);

        void SetUniformMat4f(const std::string& uniform_name, const glm::mat4& value);
        void SetUniformMat2f(const std::string& uniform_name, const glm::mat2& value);

        void PrintUniforms() const;

    private:
        int getUniformID(const std::string& uniform_name);
        void loadUniformsLocations();

        ShaderType getShaderType(const std::string& shaderTypeStr);
        ShaderProgramSource loadShaders(const std::string& filepath);
        unsigned int compileShader(const std::string& source, unsigned int type);
        unsigned int createShader(const  ShaderProgramSource& source);
    };

    class Texture
    {
    private:
        unsigned int m_RendererID;
        std::string m_FilePath;
        unsigned char* m_LocalBuffer;
        int m_Width, m_Height, m_BPP;

    public:
        Texture(const std::string& path);
        ~Texture();

        void Bind(unsigned int slot = 0) const;
        void Unbind() const;

        inline int GetWidth() const { return m_Width; }
        inline int GetHeight() const { return m_Height; }

    };

}
