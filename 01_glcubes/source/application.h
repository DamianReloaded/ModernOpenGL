#ifndef reload_glcubes01_application_H
#define reload_glcubes01_application_H

#include <display.h>
#include <state.h>

namespace reload {
    class display;
    class application
    {
        public:
                                        application     ();
            virtual                     ~application    ();

            int                         run             ();
            void                        exit            ();

        protected:
            std::unique_ptr<display>    m_display;
            reload::state*              m_state;
            bool                        m_running;

        private:
            reload::state               m_default_state;
    };
}
#endif // reload_glcubes01_application_H
