#include "OpenGLShader.h"
#include "MPE/MPEPCH.h"

#include "MPE/Core/_ASSERTS.h"
#include "MPE/Log/GlobalLog.h"

#if MPE_PLATFORM_LINUX
#    include <glad/glad.h>
#endif
#include <glm/gtc/type_ptr.hpp>

/*
I have different approach to storing few shaders in 1 file, and I belive that my way is better.
Instead of reading shader data you can add 1 line of code with some definition.
So for example for pixel shader you add "#define _TYPE_PIXEL_SHADER\n", and for vertex shader you add "#define _TYPE_VERTEX_SHADER\n".
And since glShaderSource accept array of strings, you can do it without modificating or copying orginal source.
Then shader programmer will do #ifdef _TYPE_PIXEL_SHADER ... #endif.

The biggest adventage from this method is reading shader errors.
In your method once shader programmer get shader compile error with line number, that line is far off from actual line with error.
In my method it's off by 1 line, witch is fine.
That make shader programming much much easier.

Other advantage is possibility to create common functions, definitions, variables, etc.
This is also very huge thing.
Your method can be easily changed to support common code at the top.
But in my method it can be in any order, and sometimes we want it in different order.
Or shader programmer can even use #ifdef inside function if he/she want to.

Another thing is that in my method content of file is 100% correct GLSL code. So we can use generic GLSL minifier, or other tool for GLSL.

The only advantage of your method over mine is that in your method you automaticly have information about witch shaders are in file, and witch arent.
While I have to either enforce usage of certain shader types, or assume that shaders with certain compilation error doesn't exists, or detect type by search in
shader source for string _TYPE_PIXEL_SHADER, _TYPE_VERTEX_SHADER, etc.
*/

namespace MPE
{
static GLenum ShaderTypeFromString(const std::string &type)
{
    if (type == "vertex")
    {
        return GL_VERTEX_SHADER;
    }
    if (type == "fragment" || type == "pixel")
    {
        return GL_FRAGMENT_SHADER;
    }
    else
    {
        MPE_CORE_ERROR("INVALID SHADER TYPE: {0}", type);
        MPE_CORE_ASSERT(0, "INVALID SHADER TYPE");
        return 0;
    }
}

OpenGLShader::OpenGLShader(const std::string &filepath, bool useEditorResource) : SYS_Renderer_ID(0)
{
    std::string SHADER_SOURCE = "";
    if (useEditorResource)
    {
        SHADER_SOURCE = this->ParseEditorResourcePath(filepath);
        MPE_WARN("Attempting to load shader: {0}", SHADER_SOURCE);
        SHADER_SOURCE = ValidateFile(SHADER_SOURCE);
    }
    else
    {
        SHADER_SOURCE = ValidateFile(filepath);
        MPE_WARN("Attempting to load shader: {0}", filepath);
    }

    auto SHADER_TYPE_SOURCES = PreProcess(SHADER_SOURCE);
    Compile(SHADER_TYPE_SOURCES);
    MPE_CORE_INFO("SHADER FILE {0} LOADED SUCCESSFULLY", filepath);

    std::filesystem::path path = filepath;
    SHADER_NAME = path.stem().string();
}

OpenGLShader::OpenGLShader(const std::string &name, const std::string &vertexSource, const std::string &fragmentSource) : SHADER_NAME(name), SYS_Renderer_ID(0)
{
    std::unordered_map<GLenum, std::string> SHADER_SOURCES;

#if MPE_PLATFORM_LINUX
    SHADER_SOURCES.insert(std::make_pair(GL_VERTEX_SHADER, vertexSource));
    SHADER_SOURCES.insert(std::make_pair(GL_FRAGMENT_SHADER, fragmentSource));
#else
    SHADER_SOURCES[GL_VERTEX_SHADER] = vertexSource;
    SHADER_SOURCES[GL_FRAGMENT_SHADER] = fragmentSource;
#endif

    Compile(SHADER_SOURCES);
}

OpenGLShader::~OpenGLShader()
{
    glDeleteProgram(SYS_Renderer_ID);
}

std::string OpenGLShader::ValidateFile(const std::string &filepath)
{
    std::ifstream in(filepath, std::ios::in | std::ios::binary);

    if (in.fail())
    {
        MPE_CORE_ERROR("COULD NOT LOAD SHADER FILE {0}", filepath);
        MPE_CORE_ASSERT(0, "COULD NOT LOAD SHADER FILE");
    }
    std::string result;
    in.seekg(0, std::ios::end);
    result.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&result[0], result.size());
    in.close();
    return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string &source)
{
    std::unordered_map<GLenum, std::string> shaderSources;

    const char *typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);
    while (pos != std::string::npos)
    {
        size_t eol = source.find_first_of("\r\n", pos);
        MPE_CORE_ASSERT(eol != std::string::npos, "INVALID SHADER SYNTAX");
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);
        MPE_CORE_ASSERT(ShaderTypeFromString(type), "INVALID SHADER TYPE SPECIFIER");

        size_t nextLinePos = source.find_first_not_of("\r\n", eol);
        pos = source.find(typeToken, nextLinePos);
#if MPE_PLATFORM_LINUX
        shaderSources.insert(
            std::make_pair(ShaderTypeFromString(type), source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos))));
#else
        shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
#endif
    }

    return shaderSources;
}

void OpenGLShader::Compile(std::unordered_map<GLenum, std::string> &shaders)
{
    GLuint program = glCreateProgram();

    MPE_CORE_ASSERT(shaders.size() <= OPENGL_SHADER_TYPE_AMOUNT, "TOTAL SHADER AMOUNT EXCEEDS HARDCODE LIMIT");
    std::array<GLuint, OPENGL_SHADER_TYPE_AMOUNT> glShaderIDs;
    int GLShaderIDIndex = 0;
    for (auto &&[key, value] : shaders)
    {
        GLenum type = key;
        const std::string &source = value;

        GLuint shader = glCreateShader(type);

        const GLchar *GLsource = source.c_str();
        glShaderSource(shader, 1, &GLsource, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);
            glDeleteProgram(program);

            MPE_CORE_ERROR("{0}", infoLog.data());
            MPE_CORE_ASSERT(false, "SHADER COMPILATION FAILURE.");

            break;
        }
        glAttachShader(program, shader);
        glShaderIDs[GLShaderIDIndex++] = shader;
    }

    SYS_Renderer_ID = program;

    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *) &isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);

        for (auto id : glShaderIDs)
        {
            glDeleteShader(id);
        }

        MPE_CORE_ERROR("{0}", infoLog.data());
        MPE_CORE_ASSERT(false, "SHADER FAILED TO LINK.");
        return;
    }

    for (auto id : glShaderIDs)
    {
        glDetachShader(program, id);
    }
}

void OpenGLShader::Bind() const
{
    glUseProgram(SYS_Renderer_ID);
}

void OpenGLShader::Unbind() const
{
    glUseProgram(0);
}

void OpenGLShader::SetInt1(const std::string &name, int value)
{
    InjectUniformInt1(name, value);
}

void OpenGLShader::SetInt2(const std::string &name, int values[2])
{
    InjectUniformInt2(name, values);
}

void OpenGLShader::SetInt3(const std::string &name, int values[3])
{
    InjectUniformInt3(name, values);
}

void OpenGLShader::SetInt4(const std::string &name, int values[4])
{
    InjectUniformInt4(name, values);
}

void OpenGLShader::SetFloat1(const std::string &name, float value)
{
    InjectUniformFloat1(name, value);
}

void OpenGLShader::SetFloat2(const std::string &name, const glm::vec2 &vector2)
{
    InjectUniformFloat2(name, vector2);
}

void OpenGLShader::SetFloat3(const std::string &name, const glm::vec3 &vector3)
{
    InjectUniformFloat3(name, vector3);
}

void OpenGLShader::SetFloat4(const std::string &name, const glm::vec4 &vector4)
{
    InjectUniformFloat4(name, vector4);
}

void OpenGLShader::SetMat3(const std::string &name, const glm::mat3 &matrix)
{
    InjectUniformMat3(name, matrix);
}

void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &matrix)
{
    InjectUniformMat4(name, matrix);
}

void OpenGLShader::InjectUniformInt1(const std::string &name, int value)
{
    GLint location = CheckUniform(name);
    glUniform1i(location, value);
}

void OpenGLShader::InjectUniformInt2(const std::string &name, int values[2])
{
    MPE_CORE_ASSERT(0, "MORE THAN 1 INT IS NOT SUPPORTED");
    // GLint location = CheckUniform(name);
    // glUniform2i(location, values);
}

void OpenGLShader::InjectUniformInt3(const std::string &name, int values[3])
{
    MPE_CORE_ASSERT(0, "MORE THAN 1 INT IS NOT SUPPORTED");
    // GLint location = CheckUniform(name);
    // glUniform3i(location, values);
}

void OpenGLShader::InjectUniformInt4(const std::string &name, int values[4])
{
    MPE_CORE_ASSERT(0, "MORE THAN 1 INT IS NOT SUPPORTED");
    // GLint location = CheckUniform(name);
    // glUniform4i(location, values);
}

void OpenGLShader::InjectUniformFloat1(const std::string &name, float value)
{
    GLint location = CheckUniform(name);
    glUniform1f(location, value);
}

void OpenGLShader::InjectUniformFloat2(const std::string &name, const glm::vec2 &vector2)
{
    GLint location = CheckUniform(name);
    glUniform2f(location, vector2.x, vector2.y);
}

void OpenGLShader::InjectUniformFloat3(const std::string &name, const glm::vec3 &vector3)
{
    GLint location = CheckUniform(name);
    glUniform3f(location, vector3.x, vector3.y, vector3.z);
}

void OpenGLShader::InjectUniformFloat4(const std::string &name, const glm::vec4 &vector4)
{
    GLint location = CheckUniform(name);
    glUniform4f(location, vector4.x, vector4.y, vector4.z, vector4.w);
}

void OpenGLShader::InjectUniformMat3(const std::string &name, const glm::mat3 &matrix)
{
    GLint location = CheckUniform(name);
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::InjectUniformMat4(const std::string &name, const glm::mat4 &matrix)
{
    CheckIfBound(name);
    GLint location = CheckUniform(name);

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::CheckIfBound(const std::string &name) const
{
    // Check if the shader program is bound
    GLint currentProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
    if (currentProgram != SYS_Renderer_ID)
    {
        std::cerr << "ERROR::SHADER::INJECT_UNIFORM::SHADER_PROGRAM_NOT_BOUND" << std::endl;
        return;
    }
}

GLint OpenGLShader::CheckUniform(const std::string &name) const
{
    GLint location = glGetUniformLocation(SYS_Renderer_ID, name.c_str());
    if (location == -1)
    {
        std::cerr << "ERROR::SHADER::INJECT_UNIFORM::UNIFORM_LOCATION_NOT_FOUND: " << name << std::endl;
        return -1;
    }
    return location;
}
}