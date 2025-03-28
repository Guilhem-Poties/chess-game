#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
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
inline Pos operator*(Pos const& pos, int mult)
{
    return {pos.x * 2, pos.y * 2};
}

inline bool operator==(Pos const& pos_a, Pos const& pos_b)
{
    return ((pos_a.x == pos_b.x) && (pos_a.y == pos_b.y));
}

class Board {
private:
    std::vector<std::unique_ptr<Piece>>                 _board{};
    std::vector<std::pair<Piece*, std::pair<Pos, Pos>>> move_history{};
    std::vector<std::pair<Pos, std::vector<Pos>>>       all_moves{};

public:
    Board(){};
    void generate_board();
    int  n_turns_played() const;

    Piece* at(Pos) const;

    // Functions to manage pieces movements
    std::optional<Piece*>                                 move(Pos current_pos, Pos new_pos, bool en_passant);
    void                                                  calculate_all_moves(); // Calculate all the possibles moves and stock them in the all_moves variable
    void                                                  reset_all_moves();
    std::optional<std::pair<Piece*, std::pair<Pos, Pos>>> get_last_move() const; // Get the last move from the move history
    std::vector<Pos>                                      get_piece_move(Pos pos) const;
    bool                                                  is_pos_in_piece_moveset(Pos pos_a, Pos pos_b) const; // Checks is a specific piece is in a piece moveset

    // Functions to deal wu=ith checks
    bool                                          is_check(Color player);
    bool                                          is_checkmate(Color player);
    bool                                          is_stale_mate(Color player);
    bool                                          is_king(Color piece_color, Pos piece_pos) const;
    Pos                                           king_pos(Color king_color) const;
    int                                           n_possible_moves(Color player) const;
    std::vector<std::vector<Pos>>                 king_attackers(Pos king_pos, Color king_color);
    std::vector<std::pair<Pos, std::vector<Pos>>> find_defenders(std::vector<std::vector<Pos>> attackers);
    bool                                          is_move_in_enemy_range(Pos move, Color color) const;

    // Board tiles status
    bool       is_in_board(Pos pos) const;
    Tile_State tile_state(Pos, Color color) const;
};

std::string get_case_written_coordonates(Pos coordonates); // Written the coordonates in chess language (ex : C4)

int pos_to_line(Pos pos);
Pos line_to_pos(int l);