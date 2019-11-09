#include "state.h"
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
    m_cube.create();
    m_program.load("../../../shaders/vertex.shader.c", "../../../shaders/fragment.shader.c");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void state::update ()
{

}

void state::draw ()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program.use();
    m_cube.draw(m_program.id());
}

