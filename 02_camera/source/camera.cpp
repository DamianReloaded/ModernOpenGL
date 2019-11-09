#include "camera.h"

using namespace reload;

camera::camera()
{
    //ctor
}

camera::~camera()
{

}

void camera::display (const int& _width, const int& _height)
{
    projection = glm::perspective(glm::radians(45.0f), float(_width)/float(_height), 0.1f, 1000.0f);
}

void camera::apply (transform& _transform)
{
    _transform.mvp = projection * view * _transform.model;
}

void camera::lookat (const glm::vec3& _eye, const glm::vec3& _center, const glm::vec3& _up)
{
    view = glm::lookAt(_eye, _center, _up);
}
