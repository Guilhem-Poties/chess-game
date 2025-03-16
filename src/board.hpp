#include <algorithm>
#include <iostream>
#include <memory>
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

// Structure for Positions with increase options
struct Pos {
    int x;
    int y;

    Pos incr_x(int incr) { return {this->x + incr, this->y}; };
    Pos incr_y(int incr) { return {this->x, this->y + incr}; };
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
    std::vector<std::unique_ptr<Piece>>                 _board{};
    std::vector<std::pair<Piece*, std::pair<Pos, Pos>>> move_history{};

public:
    Board(){};
    void generate_board();

    Piece* at(Pos) const;

    void   move(Pos current_pos, Pos new_pos);
    Piece* take(Pos current_pos, Pos new_pos, bool en_passant);

    // Get the last move from the move_history
    std::optional<std::pair<Piece*, std::pair<Pos, Pos>>> get_last_move() const;

    bool       is_in_board(Pos pos) const;
    Tile_State tile_state(Pos, Color color) const;
};
// Written the coordonates in chess language (ex : C4)
std::string get_case_written_coordonates(Pos coordonates);

int pos_to_line(Pos pos);
Pos line_to_pos(int l);