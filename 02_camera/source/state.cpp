#include "state.h"
#include "application.h"
#include <GL/gl.h>
using namespace reload;

state::state(application* _application) : m_application(_application)
{

}

state::~state()
{

}

void state::init ()
{
    m_cube1.create();
    m_cube2.create();
    m_cube2.transform.location = glm::vec3(-10, 0, 10);
    m_program.load("../../../shaders/vertex.shader.c", "../../../shaders/fragment.shader.c");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    m_camera.display(m_application->display()->width(), m_application->display()->height());
}

void state::update ()
{
    m_cube1.update();
    m_cube2.update();
    m_camera.lookat(glm::vec3(0,20,20), glm::vec3(0,0,0), glm::vec3(0,1,0));
}

void state::draw ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program.use();
    m_camera.apply(m_cube1.transform);
    m_cube1.draw(&m_program);
    m_camera.apply(m_cube2.transform);
    m_cube2.draw(&m_program);
}

