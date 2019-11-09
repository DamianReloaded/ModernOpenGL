#ifndef reload_glcubes01_cube_H
#define reload_glcubes01_cube_H

#include <libraries/glm.h>
#include <vector>

namespace reload {
    class cube
    {
        public:
                                cube    ();
            virtual             ~cube   ();

            void                create  ();
            void                destroy ();
            void                draw    (const uint32_t& _program_id);

        protected:
            uint32_t            m_va[1];
            uint32_t            m_vo[2];
            glm::vec3           m_rotation;
            glm::mat4           m_scale_matrix;
            std::vector<float>  m_vertices;
            std::vector<float>  m_colors;
    };
}
#endif // cube_H
