#ifndef reload_mopengl_display_implementation_H
#define reload_mopengl_display_implementation_H

#include <display.h>
#include <X11/Xlib.h>
#include <GL/glew.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <X11/extensions/Xrandr.h>
#include <X11/keysym.h>
#include <iostream>
#include <vector>
#include <deque>

namespace reload {
    class display::implementation
    {
        friend class display;

        public:
                                    implementation  ();
            virtual                 ~implementation ();

            bool                    start           ();
            void                    stop            ();
            void                    update          ();
            void                    draw            ();

            struct resource
            {
                int x;
                int y;
                int width;
                int height;
                int rotation;
            };

        protected:
            void                    init_resources  ();
            void                    add_resource    (const int& _x, const int& _y, const int& _w, const int _h, const int _rotation);

        protected:
            reload::display*        parent;
            Display*                display;
            int                     screen;
            Window                  window;
            GLXContext              context;
            XSetWindowAttributes    attributes;
            XVisualInfo*            visualinfo;
            int                     xoffset;
            int                     yoffset;
            int                     width;
            int                     height;
            bool                    fullscreen;
            uint32_t                inputmask;
            uint32_t                depth;
            static Atom             wmdelete;
            std::vector<int>        attributelist;
            std::deque<resource>    resources;
            size_t                  resource;
    };
}
#endif // implementation_H
