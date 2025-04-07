#include <imgui.h>
#include <iostream>
// #include <vector>
#include "game.hpp"
#include "glad/glad.h"
#include "glimac/Program.hpp"
#include "glm/glm.hpp"
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
    float value{0.f};

    Game game{10.f, 5};

    game.start();

    glimac::FilePath               applicationPath(argv[0]);
    std::optional<glimac::Program> program;

    GLuint vbo;
    GLuint vao;

    quick_imgui::loop(
        "Chess",
        {
            .init = [&]() {

                load_font("C:/Users/Guilhem Poties/Documents/Etudes/IMAC/S4/programmation_objet/chess-game/medias/fonts/CHEQ_TT.TTF", 32);

                program = loadProgram(applicationPath.dirPath() + "res/shader.vs.glsl", applicationPath.dirPath() + "res/shader.fs.glsl");
                program->use();

                /*VBO*/
                glGenBuffers(1, &vbo);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                Vertex3DColor vertices[] = {
                    Vertex3DColor{glm::vec3(-0.5, -0.5, 0), glm::vec3(1, 0, 0)}, // NOLINT(*modernize-use-designated-initializers)
                    Vertex3DColor{glm::vec3(0.5, -0.5, 0), glm::vec3(0, 1, 0)}, // NOLINT(*modernize-use-designated-initializers)
                    Vertex3DColor{glm::vec3(-0.5, 0.5, 0), glm::vec3(0, 0, 1)}, // NOLINT(*modernize-use-designated-initializers)

                    Vertex3DColor{glm::vec3(0.5, 0.5, 0), glm::vec3(1, 0, 0)}, // NOLINT(*modernize-use-designated-initializers)
                    Vertex3DColor{glm::vec3(0.5, -0.5, 0), glm::vec3(0, 1, 0)}, // NOLINT(*modernize-use-designated-initializers)
                    Vertex3DColor{glm::vec3(-0.5, 0.5, 0), glm::vec3(0, 0, 1)} // NOLINT(*modernize-use-designated-initializers)
                };
                glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex3DColor), vertices, GL_STATIC_DRAW);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                /*VAO*/
                glGenVertexArrays(1, &vao);
                glBindVertexArray(vao);
                glBindBuffer(GL_ARRAY_BUFFER, vbo);
                glEnableVertexAttribArray(3);
                glEnableVertexAttribArray(8);
                glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, position));
                glVertexAttribPointer(8, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3DColor), (void*)offsetof(Vertex3DColor, color));
                glBindVertexArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0); },
            // .key_callback = []()

            .loop = [&]() {
                
                glClearColor(1.f, 0.5f, 0.5f, 1.f);
                glClear(GL_COLOR_BUFFER_BIT);

                glBindVertexArray(vao);
                glDrawArrays(GL_TRIANGLES, 0, 6);
                glBindVertexArray(0);

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
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}