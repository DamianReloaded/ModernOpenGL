#include "cube.h"
#include <GL/glew.h>

using namespace reload;

cube::cube()
{
    m_scale_matrix = glm::scale(glm::vec3(1.0f,1.0f,1.0f));

    m_vertices = {
                    -1.0f,-1.0f,-1.0f,  -1.0f,-1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f, 1.0f,  -1.0f,-1.0f,-1.0f,   1.0f,-1.0f,-1.0f,
                     1.0f, 1.0f,-1.0f,   1.0f,-1.0f,-1.0f,  -1.0f,-1.0f,-1.0f,
                    -1.0f,-1.0f,-1.0f,  -1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,  -1.0f,-1.0f,-1.0f,
                    -1.0f, 1.0f, 1.0f,  -1.0f,-1.0f, 1.0f,   1.0f,-1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f,   1.0f,-1.0f,-1.0f,   1.0f, 1.0f,-1.0f,
                     1.0f,-1.0f,-1.0f,   1.0f, 1.0f, 1.0f,   1.0f,-1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f,   1.0f, 1.0f,-1.0f,  -1.0f, 1.0f,-1.0f,
                     1.0f, 1.0f, 1.0f,  -1.0f, 1.0f,-1.0f,  -1.0f, 1.0f, 1.0f,
                     1.0f, 1.0f, 1.0f,  -1.0f, 1.0f, 1.0f,   1.0f,-1.0f, 1.0f
                 };

    m_colors = {
                    0.583f,  0.771f,  0.014f,
                    0.609f,  0.115f,  0.436f,
                    0.327f,  0.483f,  0.844f,
                    0.822f,  0.569f,  0.201f,
                    0.435f,  0.602f,  0.223f,
                    0.310f,  0.747f,  0.185f,
                    0.597f,  0.770f,  0.761f,
                    0.559f,  0.436f,  0.730f,
                    0.359f,  0.583f,  0.152f,
                    0.483f,  0.596f,  0.789f,
                    0.559f,  0.861f,  0.639f,
                    0.195f,  0.548f,  0.859f,
                    0.014f,  0.184f,  0.576f,
                    0.771f,  0.328f,  0.970f,
                    0.406f,  0.615f,  0.116f,
                    0.676f,  0.977f,  0.133f,
                    0.971f,  0.572f,  0.833f,
                    0.140f,  0.616f,  0.489f,
                    0.997f,  0.513f,  0.064f,
                    0.945f,  0.719f,  0.592f,
                    0.543f,  0.021f,  0.978f,
                    0.279f,  0.317f,  0.505f,
                    0.167f,  0.620f,  0.077f,
                    0.347f,  0.857f,  0.137f,
                    0.055f,  0.953f,  0.042f,
                    0.714f,  0.505f,  0.345f,
                    0.783f,  0.290f,  0.734f,
                    0.722f,  0.645f,  0.174f,
                    0.302f,  0.455f,  0.848f,
                    0.225f,  0.587f,  0.040f,
                    0.517f,  0.713f,  0.338f,
                    0.053f,  0.959f,  0.120f,
                    0.393f,  0.621f,  0.362f,
                    0.673f,  0.211f,  0.457f,
                    0.820f,  0.883f,  0.371f,
                    0.982f,  0.099f,  0.879f
             };
}

cube::~cube()
{
    //dtor
}

void cube::create  ()
{
    glGenVertexArrays(2, &m_va[0]);
    glBindVertexArray(m_va[0]);
    glGenBuffers(2, m_vo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vo[0]);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size()*sizeof(float), &m_vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vo[1]);
    glBufferData(GL_ARRAY_BUFFER, m_colors.size()*sizeof(float), &m_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);
}

void cube::destroy ()
{

}

float angle = 0;

void cube::draw (const uint32_t& _program_id)
{
    m_rotation = glm::vec3(0,1,angle);
    angle+=0.01f;
    glm::mat4 rotx = glm::rotate(m_rotation.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 roty = glm::rotate(m_rotation.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotz = glm::rotate(m_rotation.z, glm::vec3(0.0, 0.0, 1.0));
    glm::mat4 rotmat = rotx * roty * rotz; //gotta be a better way to do this...

    glm::mat4 location = glm::translate(glm::mat4(), glm::vec3(0,0,-angle));

    // hack the camera here for now
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 1920.0f/1080.0f, 0.1f, 1000.0f);
    glm::mat4 view       = glm::lookAt(glm::vec3(0,5,5),glm::vec3(0,0,0),glm::vec3(0,1,0));
    glm::mat4 model      = location * rotmat * m_scale_matrix;
    glm::mat4 mvp        = projection * view * model;
    GLuint matrix_id     = glGetUniformLocation(_program_id, "mvp");
    glUniformMatrix4fv(matrix_id, 1, GL_FALSE, &mvp[0][0]);

    glBindVertexArray(m_va[0]);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}
