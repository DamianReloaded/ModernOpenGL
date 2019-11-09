#ifndef reload_mopengl_camera_H
#define reload_mopengl_camera_H

#include <memory>
#include <libraries/glm.h>
#include "transform.h"

namespace reload {
    class camera
    {
        public:
                        camera      ();
            virtual     ~camera     ();

            void        display     (const int& _width, const int& _height);
            void        apply       (transform& _transform);
            void        lookat      (const glm::vec3& _eye, const glm::vec3& _center, const glm::vec3& _up);

            glm::mat4   projection;
            glm::mat4   view;
    };
}
#endif // camera_H
