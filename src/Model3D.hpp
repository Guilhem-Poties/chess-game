#include <string>
#include <vector>
#include "Mesh.hpp"
#include "Shader.hpp"
#include "buffers/EBO.hpp"
#include "buffers/VAO.hpp"
#include "buffers/VBO.hpp"
#include "glm/ext/matrix_transform.hpp"

class Model3D {
public:
    void                   load_mesh(const std::string& path, const std::string& name); // 1
    void                   setup_buffers();                                             // 2
    void                   render(glmax::Shader& shader) const;                         // 3
    std::vector<glm::mat4> m_model_matrices{glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f)), glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f))};

private:
    // single mesh
    glmax::Mesh m_mesh;
    //
    // Buffers
    VAO m_vao;
    VBO m_vbo;
    EBO m_ebo;
};