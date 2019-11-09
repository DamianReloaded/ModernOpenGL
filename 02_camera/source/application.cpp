#include "application.h"

using namespace reload;

application::application() : m_default_state(this)
{
    m_running = true;
    m_display = std::make_unique<reload::display>(this);
    m_state   = &m_default_state;
}

application::~application()
{

}

int application::run ()
{
    m_display->start();

    m_state->init();

    while (m_running)
    {
        m_display->update();
        m_state->update();
        m_state->draw();
        m_display->draw();
    }

    m_display->stop();

    return 0;
}

void application::exit()
{
    m_running = false;
}

reload::display* application::display()
{
    return m_display.get();
}
