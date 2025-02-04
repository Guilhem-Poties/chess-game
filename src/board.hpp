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

class Board {
private:
    std::vector<std::optional<Piece>> _board{};

public:
    Board();

    // Piece at(int pos_x, int pos_y);

    std::optional<Piece> at(int x, int y);

    int n_piece();

    bool is_in_board(int x, int y);
    bool is_empty(int x, int y);
    bool is_ennemy(int x, int y);
    bool
};

std::string get_case_written_coordonates(std::pair<int, int> coordonates);