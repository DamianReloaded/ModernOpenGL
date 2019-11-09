#ifndef reload_glcubes01_program_H
#define reload_glcubes01_program_H

#include <iostream>
#include <string>

namespace reload {
    class program
    {
        public:
                                program     ();
            virtual             ~program    ();

            bool                load        (const std::string& _path_vertex_shader, const std::string& _path_fragment_shader);
            void                use         ();
            const uint32_t&     id          ();

        protected:
            uint32_t            m_id;

    };
}
#endif // program_H
