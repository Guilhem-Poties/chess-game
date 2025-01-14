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
    std::vector<std::vector<int>> cases;

public:
    std::vector<std::vector<int>> generate_board();

    std::string get_written_coordonates(std::pair<int, int> coordonates);
}