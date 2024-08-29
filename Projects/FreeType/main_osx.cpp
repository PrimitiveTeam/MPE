#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <map>

// #include <GL/glew.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "MPE/Vendor/GLM/GLM.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include <MPE.h>

#include "Platform/OpenGL/Utilities/OpenGLUtilities.h"

GLuint CompileShaders(bool vs_b, bool tcs_b, bool tes_b, bool gs_b, bool fs_b);

struct Character
{
    GLuint TextureID;    // ID handle of the glyph texture
    glm::ivec2 Size;     // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;      // Offset to advance to next glyph
};

void APIENTRY GLDebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* msg, const void* data)
{
    printf("%d: %s\n", id, msg);
}

int main(int argc, char* argv[])
{
    MPE::Log logger = MPE::Log("FreeTypeTest", MPE::Log::Option::CONSOLE);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "FreeTypeTest", NULL, NULL);
    glfwMakeContextCurrent(window);

    // glewInit();
    int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    MPE_CORE_ASSERT(status, "FAILED TO INITIALIZE GLAD.")
    // glEnable(GL_CULL_FACE);
    // glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCheckError();
    glViewport(0, 0, 800, 600);

    GLuint shader = CompileShaders(true, false, false, false, true);
    glUseProgram(shader);
    glCheckError();

    GLint projLoc = glGetUniformLocation(shader, "projection");
    GLint textColorLoc = glGetUniformLocation(shader, "textColor");
    GLint textSamplerLoc = glGetUniformLocation(shader, "text");

    FT_Library ft;
    FT_Init_FreeType(&ft);

    FT_Face face;
    FT_New_Face(ft, "Data//Fonts//Hack_v3_003//Hack-Regular.ttf", 0, &face);

    FT_Set_Pixel_Sizes(face, 0, 48);

    std::map<GLchar, Character> Characters;

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++)
    {
        FT_Load_Char(face, c, FT_LOAD_RENDER);

        GLuint texture;

        glGenTextures(1, &texture);
        glCheckError();

        glBindTexture(GL_TEXTURE_2D, texture);

        glCheckError();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);

        glCheckError();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // logger.warn(fmt::format("Current Texture ID: {}", (unsigned int) texture));

        Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                               glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top), (GLuint) face->glyph->advance.x};
        Characters.insert(std::pair<GLchar, Character>(c, character));

        glCheckError();
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

    GLuint vao;
    GLuint buffer;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    // Allocate memory for the buffer without initializing
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    // Set vertex attributes pointers
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 4, (GLvoid*) 0);
    glEnableVertexAttribArray(0);

    // Unbind the VAO and VBO to avoid accidental modifications
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // glUniform1i(textSamplerLoc, 0);

    std::string text("Hello OpenGL");

    while (!glfwWindowShouldClose(window))
    {
        glUseProgram(shader);
        glCheckError();
        glUniform3f(textColorLoc, 0.88f, 0.59f, 0.07f);
        glClear(GL_COLOR_BUFFER_BIT);
        GLfloat x = 1.0f;
        GLfloat y = 300.0f;
        GLfloat scale = 1.0f;

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(vao);
        std::string::const_iterator c;
        for (c = text.begin(); c != text.end(); c++)
        {
            Character ch = Characters[*c];
            GLfloat xpos = x + ch.Bearing.x * scale;
            GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

            GLfloat w = ch.Size.x * scale;
            GLfloat h = ch.Size.y * scale;
            // Update VBO for each character
            GLfloat vertices[6 * 4] = {xpos, ypos + h, 0.0f, 0.0f, xpos,     ypos, 0.0f, 1.0f, xpos + w, ypos,     1.0f, 1.0f,

                                       xpos, ypos + h, 0.0f, 0.0f, xpos + w, ypos, 1.0f, 1.0f, xpos + w, ypos + h, 1.0f, 0.0f};

            glBindBuffer(GL_ARRAY_BUFFER, buffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch.Advance >> 6) * scale;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    printf("%d", glGetError());
    return 0;
}

GLuint CompileShaders(bool vs_b, bool tcs_b, bool tes_b, bool gs_b, bool fs_b)
{

    GLuint shader_programme = glCreateProgram();

    GLuint vs, tcs, tes, gs, fs;

    if (vs_b)
    {
        FILE* vs_file;
        long vs_file_len;
        char* vertex_shader;

#ifdef MPE_PLATFORM_WINDOWS
        vs_file = fopen("Data//Shaders//vs.glsl", "rb");
#elif MPE_PLATFORM_OSX
        vs_file = fopen("Data//Shaders//3.2//vs.glsl", "rb");
#endif

        fseek(vs_file, 0, SEEK_END);
        vs_file_len = ftell(vs_file);
        rewind(vs_file);

        vertex_shader = (char*) malloc(vs_file_len + 1);

        fread(vertex_shader, vs_file_len, 1, vs_file);
        vertex_shader[vs_file_len] = '\0';
        fclose(vs_file);

        vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex_shader, NULL);
        glCompileShader(vs);

        GLint isCompiled = 0;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* error = (char*) malloc(maxLength);
            glGetShaderInfoLog(vs, maxLength, &maxLength, error);
            printf("Vertex shader error: ");
            printf(error);
            free(error);
        }

        glAttachShader(shader_programme, vs);
        free(vertex_shader);
    }
    if (tcs_b)
    {
        FILE* tcs_file;
        long tcs_file_len;
        char* tessellation_control_shader;

        tcs_file = fopen("Data//Shaders//tcs.glsl", "rb");

        fseek(tcs_file, 0, SEEK_END);
        tcs_file_len = ftell(tcs_file);
        rewind(tcs_file);

        tessellation_control_shader = (char*) malloc(tcs_file_len + 1);

        fread(tessellation_control_shader, tcs_file_len, 1, tcs_file);
        tessellation_control_shader[tcs_file_len] = '\0';
        fclose(tcs_file);

        tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
        glShaderSource(tcs, 1, &tessellation_control_shader, NULL);
        glCompileShader(tcs);

        GLint isCompiled = 0;
        glGetShaderiv(tcs, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(tcs, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* error = (char*) malloc(maxLength);
            glGetShaderInfoLog(tcs, maxLength, &maxLength, error);
            printf("Tessellation control shader error: ");
            printf(error);
            free(error);
        }

        glAttachShader(shader_programme, tcs);
        free(tessellation_control_shader);
    }
    if (tes_b)
    {
        FILE* tes_file;
        long tes_file_len;
        char* tessellation_evaluation_shader;

        tes_file = fopen("Data//Shaders//tes.glsl", "rb");

        fseek(tes_file, 0, SEEK_END);
        tes_file_len = ftell(tes_file);
        rewind(tes_file);

        tessellation_evaluation_shader = (char*) malloc(tes_file_len + 1);

        fread(tessellation_evaluation_shader, tes_file_len, 1, tes_file);
        tessellation_evaluation_shader[tes_file_len] = '\0';
        fclose(tes_file);

        tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
        glShaderSource(tes, 1, &tessellation_evaluation_shader, NULL);
        glCompileShader(tes);

        GLint isCompiled = 0;
        glGetShaderiv(tes, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(tes, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* error = (char*) malloc(maxLength);
            glGetShaderInfoLog(tes, maxLength, &maxLength, error);
            printf("Tessellation evaluation shader error: ");
            printf(error);
            free(error);
        }

        glAttachShader(shader_programme, tes);
        free(tessellation_evaluation_shader);
    }
    if (gs_b)
    {
        FILE* gs_file;
        long gs_file_len;
        char* geometry_shader;

        gs_file = fopen("Data//Shaders//gs.glsl", "rb");

        fseek(gs_file, 0, SEEK_END);
        gs_file_len = ftell(gs_file);
        rewind(gs_file);

        geometry_shader = (char*) malloc(gs_file_len + 1);

        fread(geometry_shader, gs_file_len, 1, gs_file);
        geometry_shader[gs_file_len] = '\0';
        fclose(gs_file);

        gs = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gs, 1, &geometry_shader, NULL);
        glCompileShader(gs);

        GLint isCompiled = 0;
        glGetShaderiv(gs, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(gs, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* error = (char*) malloc(maxLength);
            glGetShaderInfoLog(gs, maxLength, &maxLength, error);
            printf("Geometry shader error: ");
            printf(error);
            free(error);
        }

        glAttachShader(shader_programme, gs);
        free(geometry_shader);
    }
    if (fs_b)
    {
        FILE* fs_file;
        long fs_file_len;
        char* fragment_shader;

#ifdef MPE_PLATFORM_WINDOWS
        fs_file = fopen("Data//Shaders//fs.glsl", "rb");
#elif MPE_PLATFORM_OSX
        fs_file = fopen("Data//Shaders//3.2//fs.glsl", "rb");
#endif

        fseek(fs_file, 0, SEEK_END);
        fs_file_len = ftell(fs_file);
        rewind(fs_file);

        fragment_shader = (char*) malloc(fs_file_len + 1);

        fread(fragment_shader, fs_file_len, 1, fs_file);
        fragment_shader[fs_file_len] = '\0';
        fclose(fs_file);

        fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment_shader, NULL);
        glCompileShader(fs);

        GLint isCompiled = 0;
        glGetShaderiv(fs, GL_COMPILE_STATUS, &isCompiled);

        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            char* error = (char*) malloc(maxLength);
            glGetShaderInfoLog(fs, maxLength, &maxLength, error);
            printf("Fragment shader error: ");
            printf(error);
            free(error);
        }

        glAttachShader(shader_programme, fs);
        free(fragment_shader);
    }

    glLinkProgram(shader_programme);

    if (vs_b)
    {
        glDeleteShader(vs);
    }
    if (tcs_b)
    {
        glDeleteShader(tcs);
    }
    if (tes_b)
    {
        glDeleteShader(tes);
    }
    if (gs_b)
    {
        glDeleteShader(gs);
    }
    if (fs_b)
    {
        glDeleteShader(fs);
    }

    return shader_programme;
}