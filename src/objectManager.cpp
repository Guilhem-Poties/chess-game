#include "objectManager.hpp"

void ObjectManager::generate_objects_matrices(Board const& board)
{
    this->objects_matrices = {};
    for (int i = 0; i <= 64; i++)
        if (Piece* piece = board.at(line_to_pos(i)); piece != nullptr)
            this->objects_matrices[piece->to_string()].push_back(glm::translate(glm::mat4(1.0f), glm::vec3(1.0f * line_to_pos(i).x - 4.0f, 0.0f, 1.0f * line_to_pos(i).y - 4.0f)));
    this->objects_matrices["board"].push_back(glm::translate(glm::mat4(0.5f), glm::vec3(0.0f, 0.0f, 0.0f)));

    std::cout << "Matrices succesfully generated";
}
void ObjectManager::generate_models()
{
    for (auto object_name : this->object_names)
        this->objects_model.emplace(object_name, std::make_unique<Model3D>());

    std::cout << "Models succesfully generated";
}

void ObjectManager::init()
{
    for (auto& object_model : objects_model)
    {
        object_model.second.get()->load_mesh(object_model.first + "/" + object_model.first + ".obj", object_model.first);
        // object_model.second.get()->load_mesh("pawn/pawn.obj", "pawn");
        object_model.second.get()->setup_buffers();
    }
}

std::unordered_map<std::string, std::vector<glm::mat4>> ObjectManager::get_objects_matrices() const
{
    return this->objects_matrices;
}
Model3D* ObjectManager::get_object_model(std::string object_name) const
{
    return this->objects_model.at(object_name).get();
}
