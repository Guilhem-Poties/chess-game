#include <imgui.h>
#include <iostream>
#include <vector>
#include "game.hpp"
#include "quick_imgui/quick_imgui.hpp"

int main()
{
    float value{0.f};

    Game game{10.f, 5};

    game.board.generate_board();

    quick_imgui::loop(
        "Chess",
        /* init: */ [&]() {},
        /* loop: */
        [&]() {
            ImGui::ShowDemoWindow(); // This opens a window which shows tons of examples of what you can do with ImGui. You should check it out! Also, you can use the "Item Picker" in the top menu of that demo window: then click on any widget and it will show you the corresponding code directly in your IDE!

            ImGui::Begin("Example");

            ImGui::SliderFloat("My Value", &value, 0.f, 3.f);

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0.f, 0.f});

            for (size_t i = 0; i < 64; i++)
            {
                if (((i / 8) + (i % 8) + 1) % 2 == 0)
                {
                    if (game.is_in_move_set(line_to_pos(i)))
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.9f, 0.9f, 0.8f, 0.7f});
                    else
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.9f, 0.9f, 0.8f, 1.f});
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

                ImGui::PushID(i);

                if (ImGui::Button(game.board.at(line_to_pos(i)) == nullptr ? "" : game.board.at(line_to_pos(i))->to_char(), ImVec2{50.f, 50.f}))

                {
                    std::cout << "Clicked button " + get_case_written_coordonates(line_to_pos(i)) + "\n";
                    if (game.board.at(line_to_pos(i)) == nullptr)
                        std::cout << "Vide \n";
                    else
                        std::cout << game.board.at(line_to_pos(i))->to_string() + "\n";

                    game.update(line_to_pos(i));
                }

                ImGui::PopID();
                ImGui::PopStyleColor();

                if (i % 8 == 7)
                    ImGui::NewLine();
                else
                    ImGui::SameLine();
            }

            // for (int i = 7; i >= 0; i--)
            // {
            //     for (int j = 0; j <= 7; j++)
            //     {
            //         if ((i + j) % 2 == 0)
            //         {
            //             ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 1.f, 1.f, 1.f});
            //             // ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{0.f, 0.f, 0.f, 1.f});
            //         }
            //         else
            //         {
            //             ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{0.f, 0.f, 0.f, 1.f});
            //             // ImGui::PushStyleColor(ImGuiCol_Text, ImVec4{1.f, 1.f, 1.f, 1.f});
            //         }

            //         ImGui::PushID(i * 10 + j);
            //         if (ImGui::Button("x", ImVec2{50.f, 50.f}))
            //             std::cout << "Clicked button " + get_case_written_posonates({i, j}) + "\n";

            //         ImGui::PopID();
            //         ImGui::PopStyleColor();

            //         ImGui::SameLine();
            //     }
            //     ImGui::NewLine();
            // }

            ImGui::PopStyleVar();

            // if (ImGui::Button("1", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 1\n";
            // ImGui::SameLine(); // Draw the next ImGui widget on the same line as the previous one. Otherwise it would be below it

            // ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{1.f, 0.f, 0.f, 1.f}); // Changes the color of all buttons until we call ImGui::PopStyleColor(). There is also ImGuiCol_ButtonActive and ImGuiCol_ButtonHovered
            // ImGui::PushID(2);                                                   // When some ImGui items have the same label (for exemple the next two buttons are labeled "Yo") ImGui needs you to specify an ID so that it can distinguish them. It can be an int, a pointer, a string, etc.
            //                                                                     // You will definitely run into this when you create a button for each of your chess pieces, so remember to give them an ID!
            // if (ImGui::Button("Yo", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 2\n";
            // ImGui::PopID(); // Then pop the id you pushed after you created the widget

            // // ImGui::SameLine();
            // ImGui::PushID(3);
            // if (ImGui::Button("Yo", ImVec2{50.f, 50.f}))
            //     std::cout << "Clicked button 3\n";
            // ImGui::PopID();

            // ImGui::PopStyleColor();

            ImGui::End();
        }
    );
}