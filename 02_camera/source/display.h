#ifndef reload_mopengl_display_H
#define reload_mopengl_display_H

#include <memory>

namespace reload {
    class application;
    class display
    {
        public:
                                            display     (application* _application);
            virtual                         ~display    ();

            bool                            start       ();
            void                            stop        ();
            void                            update      ();
            void                            draw        ();

            int                             width       ();
            int                             height      ();

        protected:
            application*                    m_application;
            class                           implementation;
            friend class                    implementation;
            std::unique_ptr<implementation> imp;

    };
}
#endif // display_H
