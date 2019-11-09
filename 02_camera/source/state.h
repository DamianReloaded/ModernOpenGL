#ifndef reload_mopengl_state_H
#define reload_mopengl_state_H

#include "mesh.h"
#include "camera.h"
#include "program.h"

namespace reload {
    class application;
    class state
    {
        public:
                            state   (application* _application);
            virtual         ~state  ();

            virtual void    init    ();
            virtual void    update  ();
            virtual void    draw    ();

        protected:
            application*    m_application;
            mesh            m_cube1;
            mesh            m_cube2;
            camera          m_camera;
            program         m_program;


    };
}
#endif // state_H
