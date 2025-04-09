#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>
#include "pieces.hpp"
#include "pos.hpp"

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
    std::vector<std::unique_ptr<Piece>>                 _board{};
    std::vector<std::pair<Piece*, std::pair<Pos, Pos>>> move_history{};
    std::vector<std::vector<std::unique_ptr<Piece>>>    board_history{};
    std::vector<std::pair<Pos, std::vector<Pos>>>       all_moves{};

public:
    Board(){};
    Board(Board const& board)
        : move_history(board.move_history), all_moves(board.all_moves) {}
    void generate_board();
    int  n_turns_played() const;

    Piece* at(Pos) const;

    // Functions to manage pieces movements
    Piece*                                                move(Pos current_pos, Pos new_pos, bool en_passant, bool short_castle, bool long_castle);
    void                                                  calculate_all_moves(bool deepsearch = true); // Calculate all the possibles moves and stock them in the all_moves variable
    bool                                                  is_tower(Color piece_color, Pos piece_pos) const;
    std::optional<std::pair<Piece*, std::pair<Pos, Pos>>> get_last_move() const; // Get the last move from the move history
    std::vector<Pos>                                      get_piece_move(Pos pos) const;
    bool                                                  is_pos_in_piece_moveset(Pos pos_a, Pos pos_b) const; // Checks is a specific piece is in a piece moveset

    void promote(Pos pos, Color color, std::string option);

    // Functions to deal with checks
    bool is_check(Color player) const;
    bool is_checkmate(Color player);
    bool is_stale_mate(Color player);
    bool is_king(Color piece_color, Pos piece_pos) const;
    Pos  king_pos(Color king_color) const;
    int  n_possible_moves(Color player) const;
    bool is_last_move_repeated_position() const;
    bool is_move_future_check(Pos piece_pos, Pos move) const;
    bool is_tile_attacked(Pos move, Color color) const;

    // Board tiles status
    bool       is_in_board(Pos pos) const;
    Tile_State tile_state(Pos pos, Color color) const; // Get the tile state depending of a given color
};

std::string get_case_written_coordonates(Pos coordonates); // Written the coordonates in chess language (ex : C4)

int pos_to_line(Pos pos);
Pos line_to_pos(int l);

std::vector<std::unique_ptr<Piece>> copy_board_vector(const std::vector<std::unique_ptr<Piece>>& original);