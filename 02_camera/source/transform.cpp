#include "transform.h"

using namespace reload;

transform::transform()
{
    scale = glm::scale(glm::vec3(1.0f,1.0f,1.0f));
}

transform::~transform()
{

}

void transform::update()
{
    glm::mat4 rotx = glm::rotate(rotation.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 roty = glm::rotate(rotation.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotz = glm::rotate(rotation.z, glm::vec3(0.0, 0.0, 1.0));
    rotmat = rotx * roty * rotz;
    locmat = glm::translate(glm::mat4(), location);
    model  = locmat * rotmat * scale;
}
