#ifndef reload_mopengl_mesh_H
#define reload_mopengl_mesh_H

#include <libraries/glm.h>
#include <vector>
#include "transform.h"

namespace reload {
    class program;

    class mesh
    {
        public:
                                mesh    ();
            virtual             ~mesh   ();

            void                create  ();
            void                destroy ();
            void                update  ();
            void                draw    (reload::program* _program);

            reload::transform   transform;

        protected:
            uint32_t            m_va[1];
            uint32_t            m_vo[2];
            std::vector<float>  m_vertices;
            std::vector<float>  m_colors;
    };
}
#endif // mesh_H
