#ifndef reload_mopengl_transform_H
#define reload_mopengl_transform_H

#include <libraries/glm.h>

namespace reload {
    class transform
    {
        public:
                        transform   ();
            virtual     ~transform  ();

            void        update      ();

            glm::vec3   rotation;
            glm::vec3   location;
            glm::mat4   locmat;
            glm::mat4   rotmat;
            glm::mat4   scale;
            glm::mat4   mvp;
            glm::mat4   model;
    };
}
#endif // transform_H
