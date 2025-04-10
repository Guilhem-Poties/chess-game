#include "objectManager.hpp"

void ObjectManager::generate_objects_matrices(Board const& board)
{
    this->objects_matrices = {};
    for (int i = 0; i <= 64; i++)
    {
        Pos pos = line_to_pos(i);
        if (Piece* piece = board.at(pos); piece != nullptr)
            this->objects_matrices[piece->to_string()].push_back(this->get_model_matrix(pos));
    }
    this->objects_matrices["board"].push_back(glm::translate(glm::mat4(0.5f), glm::vec3(0.0f, 0.0f, 0.0f)));

    // std::cout << "Matrices succesfully generated \n";s
}
void ObjectManager::generate_models()
{
    for (auto object_name : this->object_names)
        this->objects_model.emplace(object_name, std::make_unique<Model3D>());

    std::cout << "Models succesfully generated \n";
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

void ObjectManager::animate(Board const& board, float& t, float s)
{
    if (!this->animating)
        this->animating = true;

    if (board.get_last_move() != std::nullopt)
    {
        this->objects_matrices = {};
        auto last_move         = board.get_last_move().value();

        auto source_x = (float)last_move.second.first.x;
        auto source_y = (float)last_move.second.first.y;
        auto target_x = (float)last_move.second.second.x;
        auto target_y = (float)last_move.second.second.y;

        auto obj_x = (s - t) * source_x + t * target_x;
        auto obj_y = (s - t) * source_y + t * target_y;

        for (int i = 0; i <= 64; i++)
        {
            Pos pos = line_to_pos(i);

            if (pos == last_move.second.second)
            {
                this->objects_matrices[last_move.first.first->to_string()].push_back(this->get_model_matrix(obj_x, obj_y));
                if (last_move.first.second != nullptr)
                {
                    if (t <= s * 0.9f)
                        this->objects_matrices[last_move.first.second->to_string()].push_back(this->get_model_matrix(target_x, target_y));
                    else
                    {
                        float t_norm = (t - s * 0.9f) / s * 0.1f;
                        float t_exp  = pow(t_norm, 3);

                        this->objects_matrices[last_move.first.second->to_string()].push_back(this->get_model_matrix((target_x + target_x * (t_exp)), (target_y + target_y * (t_exp))));
                    }
                }
            }
            else if (Piece* piece = board.at(pos); piece != nullptr)
                this->objects_matrices[piece->to_string()].push_back(this->get_model_matrix(pos));
        }
        this->objects_matrices["board"].push_back(glm::translate(glm::mat4(0.5f), glm::vec3(0.0f, 0.0f, 0.0f)));
    }

    t += 0.02f;
    if (((int)(t + 0.002f)) == (int)(s))
    {
        this->animating = false;
        t               = 0.0f;
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
glm::mat4 ObjectManager::get_model_matrix(Pos pos)
{
    return glm::translate(glm::mat4(0.5f), glm::vec3(2 * (1.0f * pos.x - 3.5f), 0.0f, 2 * (1.0f * pos.y - 3.5f)));
}
glm::mat4 ObjectManager::get_model_matrix(float x, float y)
{
    return glm::translate(glm::mat4(0.5f), glm::vec3(2 * (1.0f * x - 3.5f), 0.0f, 2 * (1.0f * y - 3.5f)));
}