#include <algorithm>
#include <iostream>
#include <memory>
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

struct Pos {
    int x;
    int y;
};

inline Pos operator+(Pos const& pos_a, Pos const& pos_b)
{
    return {pos_a.x + pos_b.x, pos_a.y + pos_b.y};
}
inline Pos operator-(Pos const& pos_a, Pos const& pos_b)
{
    return {pos_a.x - pos_b.x, pos_a.y - pos_b.y};
}
inline bool operator==(Pos const& pos_a, Pos const& pos_b)
{
    return ((pos_a.x == pos_b.x) && (pos_a.y == pos_b.y));
}

class Board {
private:
    std::vector<std::unique_ptr<Piece>> _board{};

public:
    Board(){};
    void generate_board();

    Piece* at(Pos) const;

    Piece* move(Pos current_pos, Pos new_pos);
    Piece* take(Pos);

    bool       is_in_board(Pos pos) const;
    Tile_State tile_state(Pos, Color color) const;
};

std::string get_case_written_coordonates(Pos coordonates);

int coord_to_line(Pos pos);
Pos line_to_coord(int l);