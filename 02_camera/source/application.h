#ifndef reload_mopengl_application_H
#define reload_mopengl_application_H

#include <memory>
#include <display.h>
#include <state.h>

namespace reload {
    class display;
    class application
    {
        public:
                                                application     ();
            virtual                             ~application    ();

            int                                 run             ();
            void                                exit            ();
            reload::display*                    display         ();

        protected:
            std::unique_ptr<reload::display>    m_display;
            reload::state*                      m_state;
            bool                                m_running;
            reload::state                       m_default_state;
    };
}
#endif // reload_mopengl_application_H
