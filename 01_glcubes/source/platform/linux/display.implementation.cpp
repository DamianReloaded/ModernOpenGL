#include "display.implementation.h"
#include "application.h"

using namespace reload;

Atom display::implementation::wmdelete;

display::implementation::implementation()
{
    width = 1024;
    height = 768;
    fullscreen = false;
    resource = 0;
    inputmask = FocusChangeMask | ButtonPressMask | ButtonReleaseMask   | ButtonMotionMask | PointerMotionMask |
                KeyPressMask    | KeyReleaseMask  | StructureNotifyMask | EnterWindowMask  | LeaveWindowMask;

    attributelist = { GLX_RGBA,
                      GLX_DEPTH_SIZE,       24,
                      GLX_STENCIL_SIZE,     8,
                      GLX_DOUBLEBUFFER,     True,
                      GLX_SAMPLE_BUFFERS,   1,
                      GLX_SAMPLES,          8
                    };
}

display::implementation::~implementation()
{

}

bool display::implementation::start()
{
    int         glx_major_version;
    int         glx_minor_version;

    display    = XOpenDisplay(0);
    screen     = DefaultScreen(display);
    visualinfo = glXChooseVisual(display, screen, &attributelist[0]);
    if (visualinfo==NULL)
    {
        attributelist[19] = False;
        visualinfo = glXChooseVisual(display, screen, &attributelist[0]);
    }

    init_resources();

    glXQueryVersion(display, &glx_major_version, &glx_minor_version);

    context                         = glXCreateContext(display, visualinfo, 0, GL_TRUE);
    attributes.colormap             = XCreateColormap(display, RootWindow(display, visualinfo->screen), visualinfo->visual, AllocNone);
    attributes.background_pixmap    = None;
    attributes.border_pixel         = 0;
    attributes.event_mask           = ExposureMask | KeyPressMask | ButtonPressMask | StructureNotifyMask;

    if (fullscreen)
    {
        attributes.override_redirect = True;
        window = XCreateWindow(display, RootWindow(display, visualinfo->screen),
                               resources[resource].x, resources[resource].y, resources[resource].width, resources[resource].height,
                               0, visualinfo->depth, InputOutput, visualinfo->visual,
                               CWBorderPixel | CWColormap | CWEventMask | CWOverrideRedirect, &attributes);
        XWarpPointer(display, None, window, 0,0,0,0,0,0);
        XMapRaised(display, window);
        XGrabKeyboard(display, window, True, GrabModeAsync, GrabModeAsync, CurrentTime);
        XGrabPointer(display, window, True, ButtonPressMask, GrabModeAsync, GrabModeAsync, window, None, CurrentTime);
    }
    else
    {
        window = XCreateWindow(display, RootWindow(display, visualinfo->screen),
                               0, 0, resources[resource].width, resources[resource].height,
                               0, visualinfo->depth, InputOutput, visualinfo->visual,
                               CWBorderPixel | CWColormap | CWEventMask, &attributes);
        XSetStandardProperties(display, window, "title", "title2", None, NULL, 0, NULL);
        XMapRaised(display, window);
    }

    XFree(visualinfo);

    wmdelete = XInternAtom(display, "WM_DELETE_WINDOW", True);
    XSetWMProtocols(display, window, &wmdelete, 1);
    glXMakeCurrent(display, window, context);

    Window      dummywindow;
    uint32_t    dummyborder;
    int         x=0, y=0;
    XGetGeometry(display, window, &dummywindow, &x, &y, (unsigned int*)&width, (unsigned int*)&height, &dummyborder, &depth);

    if (glXIsDirect(display, context)) {} //do something
    XSelectInput(display, window, inputmask);
    glewInit();

    return true;
}

void display::implementation::update()
{
    XEvent event;
    while (XPending(display))
    {
        XNextEvent(display, &event);

        switch(event.type)
        {
            case ClientMessage:
            {
                if ((Atom)event.xclient.data.l[0] == wmdelete)
                {
                    parent->m_application->exit();
                }
            }
            break;

            case DestroyNotify:
            {

            }
            break;

            case Expose:
            {
                draw();
            }
            break;

            case ButtonPress:
            {
                switch(event.xbutton.button)
                {
                    case 1: parent->m_application->exit(); break;
                }
            }
            break;
        }
    }
}

void display::implementation::stop()
{

}

void display::implementation::draw()
{
    if (attributelist[19])
    {
        glXSwapBuffers(display, window);
    }
}

void display::implementation::init_resources ()
{
    resources.clear();
    XRRScreenResources* res = XRRGetScreenResources(display, RootWindow(display,visualinfo->screen));
    for (int i=0; i<res->noutput; i++)
    {
        auto info = XRRGetOutputInfo(display, res, res->outputs[i]);
        for (int c=0; c<info->ncrtc; c++)
        {
            auto crtcinfo = XRRGetCrtcInfo(display, res, res->crtcs[c]);
            add_resource(crtcinfo->x, crtcinfo->y, crtcinfo->width, crtcinfo->height, crtcinfo->rotation);
            XRRFreeCrtcInfo(crtcinfo);
        }
        XRRFreeOutputInfo(info);
    }
    if (resource>resources.size()-1) resource = 0;
}

void display::implementation::add_resource (const int& _x, const int& _y, const int& _w, const int _h, const int _rotation)
{
    if (_w<1 || _h<1) return;
    for (size_t i=0; i<resources.size(); i++)
    {
        if (resources[i].x == _x && resources[i].y == _y && resources[i].width == _w && resources[i].height == _h && resources[i].rotation == _rotation)
        {
            return;
        }
    }
    resources.resize(resources.size()+1);
    resources.back().x        = _x;
    resources.back().y        = _y;
    resources.back().width    = _w;
    resources.back().height   = _h;
    resources.back().rotation = _rotation;

    if (resources.back().width == width && resources.back().height == height ) resource = resources.size()-1;
}
