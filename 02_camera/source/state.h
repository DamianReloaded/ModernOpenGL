#ifndef reload_glcubes01_state_H
#define reload_glcubes01_state_H

#include "cube.h" // hack a cube here for now
#include "program.h" // hack a shader program

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
            cube            m_cube;
            program         m_program;


    };
}
#endif // state_H
