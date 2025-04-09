#include <unordered_map>
#include "Model3D.hpp"
#include "board.hpp"
#include "glm/ext/matrix_transform.hpp"

class ObjectManager {
public:
    void generate_models();
    void generate_objects_matrices(Board const& board);

    void init();

    std::unordered_map<std::string, std::vector<glm::mat4>> get_objects_matrices() const;
    Model3D*                                                get_object_model(std::string object_name) const;

private:
    std::unordered_map<std::string, std::vector<glm::mat4>>   objects_matrices;
    std::unordered_map<std::string, std::unique_ptr<Model3D>> objects_model;

    std::vector<std::string> object_names{"king", "queen", "bishop", "knight", "tower", "pawn", "board"};
    // std::vector<std::unordered_map<std::string, std::string>> object_path_by_name{"king", "queen", "bishop", "knight", "tower", "pawn"};
};
