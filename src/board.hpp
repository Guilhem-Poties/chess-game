#include <algorithm>
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
    std::vector<Piece> pieces{};

public:
    Board();

    Piece at(int pos_x, int pos_y);

    int n_piece();
};

std::string get_case_written_coordonates(std::pair<int, int> coordonates);