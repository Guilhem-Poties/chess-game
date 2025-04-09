#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Camera.hpp"
#include "Shader.hpp"
#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "objectManager.hpp"
#include "quick_imgui/quick_imgui.hpp"

struct Vertex3DColor {
    glm::vec3 position;
    glm::vec3 color;
};

void load_font(const std::string& path, const float size)
{
    ImGuiIO& io = ImGui::GetIO();
    if (io.Fonts->AddFontFromFileTTF(path.c_str(), size))
        std::cout << "Font successfully loaded : " << path << "\n";
    else
        std::cerr << "Failed to load font: " << path << " :("
                  << "\n";
}

int main(int argc, char** argv)
{
    int           window_width  = 1280;
    int           window_height = 720;
    glmax::Shader shader;
    glmax::Camera camera{true};
    //
    Model3D model;

    Game game{10.f, 5};
    game.start();

    ObjectManager objectManager;
    objectManager.generate_objects_matrices(game.board);
    objectManager.generate_models();

    quick_imgui::loop(
        "Chess",
        {
            .init = [&]() {
                load_font("C:/Users/Guilhem Poties/Documents/Etudes/IMAC/S4/programmation_objet/chess-game/assets/fonts/CHEQ_TT.TTF", 32);
                 
                shader.load_shader("model.vs.glsl", "model.fs.glsl");
                model.load_mesh("pawn/pawn.obj", "pawn");
                model.setup_buffers(); 
                objectManager.init(); },
            // .key_callback = []()

            .loop = [&]() {
                //
                glClearColor(0.847f, 0.82f, 0.929f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                //
                for (auto model_matrices : objectManager.get_objects_matrices())
                {
                    for (auto model_matrix : model_matrices.second)
                    {
                        glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(window_width) / static_cast<float>(window_height), 0.1f, 100.0f);

                        shader.use();

                        // MVP
                        shader.set_uniform_matrix_4fv("model", model_matrix);
                        shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
                        shader.set_uniform_matrix_4fv("projection", projection);

                        // LIGHT SETTINGS
                        shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
                        shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

                        // CAMERA SETTINGS
                        shader.set_uniform_3fv("viewPos", camera.get_position());

                        // MODEL RENDER
                        objectManager.get_object_model(model_matrices.first)->render(shader);
                    }
                }

                ImGui::Begin("Chess");

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f});

                for (int i = 0; i < 64; i++)
                {
                    int n_pop{1}; // Count the number of pop to do at the end of the Imguiloop
                    if (((i / 8) + (i % 8) + 1) % 2 == 0)
                    {
                        if (game.is_in_move_set(line_to_pos(i)))
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.9f, 0.9f, 0.8f, 0.7f});
                        else
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.8f, 0.9f, 0.7f, 1.f});
                        // ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{0.f, 0.f, 0.f, 1.f});
                    }
                    else
                    {
                        if (game.is_in_move_set(line_to_pos(i)))
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.35f, 0.55f, 0.25f, 0.7f});
                        else
                            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.35f, 0.55f, 0.25f, 1.f});
                        // ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.f, 1.f, 1.f, 1.f});
                    }

                    if (Piece* piece = game.board.at(line_to_pos(i)); piece != nullptr)
                    {
                        if (piece->get_color() == Color::white)
                            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.f, 1.f, 1.f, 1.f});
                        else
                            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{0.1f, 0.1f, 0.1f, 1.f});
                        n_pop++;
                    }

                    ImGui::PushID(i);

                    if (ImGui::Button(game.board.at(line_to_pos(i)) == nullptr ? "" : game.board.at(line_to_pos(i))->to_char(), ImVec2{50.f, 50.f}))
                    {
                        if (!game.is_promoting())
                        {
                            game.update(line_to_pos(i));
                            objectManager.generate_objects_matrices(game.board);
                        }
                        else std::cout << "No \n";
                        
                    }

                    ImGui::PopID();
                    ImGui::PopStyleColor(n_pop);

                    if (i % 8 != 7)
                        ImGui::SameLine();
                }
                ImGui::PopStyleVar();

                ImGui::End();

                if (game.is_promoting())
                {
                    ImGui::Begin("promotion");

                    std::vector<std::string> promote_options {"t","j","n","w"};

                    for (auto option : promote_options) 
                    {
                        if (ImGui::Button(option.c_str(), ImVec2{50.f, 50.f})){
                            game.promote(option);
                            objectManager.generate_objects_matrices(game.board);
                        }
                        ImGui::SameLine();
                    }
                        
                    ImGui::End();
                    

                } },

            .key_callback             = [&](int key, int scancode, int action, int mods) { std::cout << "Key: " << key << " Scancode: " << scancode << " Action: " << action << " Mods: " << mods << '\n'; },
            .mouse_button_callback    = [&](int button, int action, int mods) { std::cout << "Button: " << button << " Action: " << action << " Mods: " << mods << '\n'; },
            .cursor_position_callback = [&](double xpos, double ypos) { camera.track_ball_move_callback(xpos, ypos); },
            .scroll_callback          = [&](double xoffset, double yoffset) { camera.process_scroll(yoffset); },
            .window_size_callback     = [&](int width, int height) { std::cout << "Resized: " << width << ' ' << height << '\n'; },

        }
    );
}