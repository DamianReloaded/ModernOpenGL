#include "display.implementation.h"


using namespace reload;

display::display(application* _application) : m_application(_application)
{
    imp = std::make_unique<implementation>();
    imp->parent = this;
}

display::~display()
{

}

bool display::start ()
{
    return imp->start();
}

void display::stop ()
{
    imp->stop();
}

void display::update ()
{
    imp->update();
}

void display::draw ()
{
    imp->draw();
}

int display::width ()
{
    return imp->width;
}

int display::height ()
{
    return imp->height;
}
