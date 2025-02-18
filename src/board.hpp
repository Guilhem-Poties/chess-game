#include <algorithm>
#include <optional>
#include <string>
#include <utility>
#include <vector>
#include "pieces.hpp"

#pragma once

#ifndef BOARD_ATTRIBUTES
// Vector used to associate the y coordonate
const std::vector<std::string> coordonates_letter{"A", "B", "C", "D", "E", "F", "G", "H"};
#endif

enum class Tile_State : int {
    enemy,
    ally,
    empty
};

class Board {
private:
    std::vector<std::optional<Piece>> _board{};

public:
    Board();

    int  coord_to_line(int x, int y);
    void line_to_coord();

    std::optional<Piece> at(int x, int y);

    std::optional<Piece> move(int current_x, int current_y, int new_x, int new_y);
    std::optional<Piece> take(int x, int y);

    bool       is_in_board(int x, int y) const;
    Tile_State tile_state(int x, int y, Color color) const;
};

std::string get_case_written_coordonates(std::pair<int, int> coordonates);