#include <imgui.h>
#include <glm/glm.hpp>
#include <iostream>
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "game.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/fwd.hpp"
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
    Game game{10.f, 5};
    game.start();

    quick_imgui::loop(
        "Chess",
        {
            .init = [&]() { load_font("C:/Users/Guilhem Poties/Documents/Etudes/IMAC/S4/programmation_objet/chess-game/medias/fonts/CHEQ_TT.TTF", 32); },

            .loop = [&]() {

                /******** OpenGL ********/

            ImGui::Begin("Chess");

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f});

            for (int i = 63; i >=0; i--)
            {
                int n_pop {1}; // Count the number of pop to do at the end of the Imguiloop
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
                
                if(Piece* piece = game.board.at(line_to_pos(i)); piece != nullptr){
                    if (piece->get_color() == Color::white)
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.f, 1.f, 1.f, 1.f});
                    else
                        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{0.1f, 0.1f, 0.1f, 1.f});
                    n_pop++;
                }

                ImGui::PushID(i);

                if (ImGui::Button(game.board.at(line_to_pos(i)) == nullptr ? "" : game.board.at(line_to_pos(i))->to_char(), ImVec2{50.f, 50.f}))
                    game.update(line_to_pos(i));
                

                ImGui::PopID();
                ImGui::PopStyleColor(n_pop);

                if (i % 8 != 0)
                    ImGui::SameLine();
            }
            ImGui::PopStyleVar();

            ImGui::End(); },

        }
    );
}