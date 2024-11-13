#include "Shaders.h"

namespace Graphics
{
    Shader::Shader(const std::string& filepath) :
        m_RendererID(0), m_FilePath(filepath), m_Uniforms({})
    {
        ShaderProgramSource source = loadShaders(filepath);
        m_RendererID = createShader(source);
        loadUniformsLocations();
    }

    Shader::~Shader()
    {
        glCall(glDeleteProgram(m_RendererID));
    }

    void Shader::Bind() const
    {
        glCall(glUseProgram(m_RendererID));
    }

    void Shader::Unbind() const
    {
        glCall(glUseProgram(0));
    }

    void Shader::SetSampler(const std::string& uniform_name, const unsigned int count, const int* value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform1iv(location, count, value));
    }

    void Shader::SetUniform1f(const std::string& uniform_name, const float& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform1f(location, value));
    }
    void Shader::SetUniform2f(const std::string& uniform_name, const glm::vec2& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform2f(location, value.x,value.y));
    }
    void Shader::SetUniform3f(const std::string& uniform_name, const glm::vec3& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform3f(location, value.x, value.y, value.z));
    }
    void Shader::SetUniform4f(const std::string& uniform_name, const glm::vec4& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform4f(location, value.x, value.y, value.z, value.w));
    }

    void Shader::SetUniform1i(const std::string& uniform_name, const int& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform1i(location, value));
    }
    void Shader::SetUniform2i(const std::string& uniform_name, const glm::ivec2& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform2i(location, value.x, value.y));
    }
    void Shader::SetUniform3i(const std::string& uniform_name, const glm::ivec3& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform3i(location, value.x, value.y, value.z));
    } 
    void Shader::SetUniform4i(const std::string& uniform_name, const glm::ivec4& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniform4i(location, value.x, value.y, value.z, value.w));
    }

    void Shader::SetUniformMat4f(const std::string& uniform_name, const glm::mat4& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]));
    }
    void Shader::SetUniformMat2f(const std::string& uniform_name, const glm::mat2& value)
    {
        int location = getUniformID(uniform_name);
        glCall(glUniformMatrix2fv(location, 1, GL_FALSE, &value[0][0]));
    }

    void  Shader::PrintUniforms() const
    {
        for (const auto& pair : m_Uniforms)
        {
            std::cout << pair.first << " location: " << pair.second <<std::endl;
        }
    }
    void Shader::loadUniformsLocations()
    {
        for (const auto& pair : m_Uniforms)
        {
            std::string uniform_name = pair.first;
            glCall(int location = glGetUniformLocation(m_RendererID, uniform_name.c_str()));
            m_Uniforms[uniform_name] = location;
        }
    }

    int Shader::getUniformID(const std::string& uniforn_name) 
    {
        return m_Uniforms[uniforn_name];
    }

    ShaderProgramSource Shader::loadShaders(const std::string& filepath)
    {
        std::ifstream stream(filepath);
        std::string line;
        if (!stream.is_open())
        {
            std::cout << "Nie mo¿na otworzyæ pliku: " + filepath << std::endl;
        }

        std::stringstream ss[6];
        ShaderType shaderType = ShaderType::UNKNOWN;

        while (getline(stream, line))
        {
            //std::cout << line << std::endl;
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    shaderType = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    shaderType = ShaderType::FRAGMENT;
                else if (line.find("geometry") != std::string::npos)
                    shaderType = ShaderType::GEOMETRY;
                else if (line.find("tessellation_control") != std::string::npos)
                    shaderType = ShaderType::TESSELLATION_CONTROL;
                else if (line.find("tessellation_evaluation") != std::string::npos)
                    shaderType = ShaderType::TESSELLATION_EVALUATION;
                else if (line.find("compute") != std::string::npos)
                    shaderType = ShaderType::COMPUTE;

            }
            else
            {

                if (line.find("uniform") != std::string::npos)
                {
                    // Parse uniform declaration
                    std::istringstream iss(line);
                    std::string token;
                    std::vector<std::string> tokens;
                    while (iss >> token)
                    {
                        tokens.push_back(token);
                    }
                    if (tokens.size() >= 3)
                    {
                        //may be usful later
                        std::string uniformTypeString = tokens[1];

                        std::string uniformName = tokens[2].substr(0, tokens[2].size() - 1);   
                        //std::cout << uniformName << std::endl;
                        m_Uniforms[uniformName] = -1;
                    }
                }

                if (shaderType != ShaderType::UNKNOWN)
                {
                    ss[(int)shaderType] << line << "\n";
                }
            }

        }
        return { ss[(int)VERTEX].str(),
                ss[(int)FRAGMENT].str(),
                ss[(int)GEOMETRY].str(),
                ss[(int)TESSELLATION_CONTROL].str(),
                ss[(int)TESSELLATION_EVALUATION].str(),
                ss[(int)COMPUTE].str() };
    }
    unsigned int Shader::compileShader(const std::string& sourceCode, unsigned int type)
    {
        glCall(unsigned int shader_id = glCreateShader(type));
        const char* src = sourceCode.c_str();
        glCall(glShaderSource(shader_id, 1, &src, nullptr));
        glCall(glCompileShader(shader_id));

        int result;
        glCall(glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result));
        if (result == GL_FALSE)
        {
            int length;
            glCall(glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length));
            char* message = new char[length];
            glCall(glGetShaderInfoLog(shader_id, length, &length, message));

            std::cout << "Failed to compile sheader of type: " << type << std::endl;
            std::cout << message << std::endl;

            delete[] message;
            glCall(glDeleteShader(shader_id));
            return 0;
        }

        return shader_id;
    }
    unsigned int Shader::createShader(const  ShaderProgramSource& source)
    {
        unsigned int vs, fs, geo, tess_c, tess_e, comp;
        glCall(unsigned int program = glCreateProgram());

        bool vs_exists = !source.VertexSource.empty();
        bool fs_exists = !source.FragmentSource.empty();
        bool geo_exists = !source.GeometrySource.empty();
        bool tess_c_exists = !source.TessellationControlSource.empty();
        bool tess_e_exists = !source.TessellationEvaluationSource.empty();
        bool comp_exists = !source.ComputeSource.empty();

        if (vs_exists)
        {
            vs = compileShader(source.VertexSource, GL_VERTEX_SHADER);
            glCall(glAttachShader(program, vs));
        }
        if (fs_exists)
        {
            fs = compileShader(source.FragmentSource, GL_FRAGMENT_SHADER);
            glCall(glAttachShader(program, fs));
        }
        if (geo_exists)
        {
            geo = compileShader(source.GeometrySource, GL_GEOMETRY_SHADER);
            glCall(glAttachShader(program, geo));
        }
        if (tess_c_exists)
        {
            tess_c = compileShader(source.TessellationControlSource, GL_TESS_CONTROL_SHADER);
            glCall(glAttachShader(program, tess_c));
        }
        if (tess_e_exists)
        {
            tess_e = compileShader(source.TessellationEvaluationSource, GL_TESS_EVALUATION_SHADER);
            glCall(glAttachShader(program, tess_e));
        }
        if (comp_exists)
        {
            comp = compileShader(source.ComputeSource, GL_COMPUTE_SHADER);
            glCall(glAttachShader(program, comp));
        }

        glCall(glLinkProgram(program));
        glCall(glValidateProgram(program));

        if (vs_exists)
        {
            glCall(glDeleteShader(vs));
        }
        if (fs_exists)
        {
            glCall(glDeleteShader(fs));
        }
        if (geo_exists)
        {
            glCall(glDeleteShader(geo));
        }
        if (tess_c_exists)
        {
            glCall(glDeleteShader(tess_c));
        }
        if (tess_e_exists)
        {
            glCall(glDeleteShader(tess_e));
        }
        if (comp_exists)
        {
            glCall(glDeleteShader(comp));
        }

        return program;
    }

    ShaderType Shader::getShaderType(const std::string& shaderTypeStr)
    {

        if (shaderTypeStr == "vertex")                       return VERTEX;
        else if (shaderTypeStr == "fragment")                return FRAGMENT;
        else if (shaderTypeStr == "geometry")                return GEOMETRY;
        else if (shaderTypeStr == "tessellation_control")    return TESSELLATION_CONTROL;
        else if (shaderTypeStr == "tessellation_evaluation") return TESSELLATION_EVALUATION;
        else if (shaderTypeStr == "compute")                 return COMPUTE;
        return ShaderType::UNKNOWN;
    }

    Texture::Texture(const std::string& path):
        m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), 
        m_Width(0), m_Height(0), m_BPP(0)
    {
        stbi_set_flip_vertically_on_load(1);
        m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
        if (!m_LocalBuffer) 
        {
            std::cout << "Failed to load texture: " << path << std::endl;
            ASSERT(false);
        }
        glCall(glGenTextures(1, &m_RendererID));
        glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        glCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        glCall(glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,m_Width,m_Height,0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
        glCall(glBindTexture(GL_TEXTURE_2D, 0));

        if (m_LocalBuffer)
        {
            stbi_image_free(m_LocalBuffer);
        }
    }
    Texture::~Texture()
    {
        glCall(glDeleteTextures(1, &m_RendererID));
    }
    void Texture::Bind(unsigned int slot) const
    {
        glCall(glActiveTexture(GL_TEXTURE0 + slot));
        glCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }
    void Texture::Unbind() const
    {
        glCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

 
}