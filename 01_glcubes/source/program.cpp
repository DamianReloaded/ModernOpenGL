#include "program.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <GL/glew.h>
using namespace reload;

program::program()
{
    //ctor
}

program::~program()
{
    //dtor
}

const uint32_t& program::id()
{
    return m_id;
}

bool program::load (const std::string& _path_vertex_shader, const std::string& _path_fragment_shader)
{
    uint32_t vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    uint32_t fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    int result = GL_FALSE;
    int info = 0;

    std::string vertex_shader_code;
    std::ifstream vertex_shader_file(_path_vertex_shader, std::ios::in);
    if (vertex_shader_file.is_open())
    {
        std::stringstream sstr;
        sstr << vertex_shader_file.rdbuf();
        vertex_shader_code = sstr.str();
        vertex_shader_file.close();

        char const* ptr = vertex_shader_code.c_str();
        glShaderSource(vertex_shader_id, 1, &ptr, NULL);
        glCompileShader(vertex_shader_id);
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &info);
        if (info > 0)
        {
            std::vector<char> vertex_shader_error_message(info+1);
            glGetShaderInfoLog(vertex_shader_id, info, NULL, &vertex_shader_error_message[0]);
            return false;
        }
    }
    else
    {
        return false;
    }


    std::string fragment_shader_code;
    std::ifstream fragment_shader_file(_path_fragment_shader, std::ios::in);
    if (fragment_shader_file.is_open())
    {
        std::stringstream sstr;
        sstr << fragment_shader_file.rdbuf();
        fragment_shader_code = sstr.str();
        fragment_shader_file.close();

        char const* ptr = fragment_shader_code.c_str();
        glShaderSource(fragment_shader_id, 1, &ptr, NULL);
        glCompileShader(fragment_shader_id);
        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &info);
        if (info > 0)
        {
            std::vector<char> fragment_shader_error_message(info+1);
            glGetShaderInfoLog(fragment_shader_id, info, NULL, &fragment_shader_error_message[0]);
            return false;
        }
    }
    else
    {
        return false;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_shader_id);
    glAttachShader(m_id, fragment_shader_id);
    glLinkProgram(m_id);
    glGetProgramiv(m_id, GL_LINK_STATUS, &result);
    glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &info);
    if (info > 0)
    {
        std::vector<char> program_error_message(info+1);
        glGetProgramInfoLog(m_id, info, NULL, &program_error_message[0]);
        return false;
    }

    glDetachShader(m_id, vertex_shader_id);
    glDetachShader(m_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return true;
}

void program::use()
{
    glUseProgram(m_id);
}
