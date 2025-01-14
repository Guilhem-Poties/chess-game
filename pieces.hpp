#include <cstddef>
#include <utility>
#include <vector>

#pragma once

#ifndef PIECES_ATTRIBUTES
const std::vector<int> piece_value_by_type{9, 5, 3, 3, 1, 0};

#endif

enum class Piece_type : int {
    Queen,
    Tower,
    Bishop,
    Knight,
    Pawn,
    King
};

enum class Color : bool {
    black,
    white
};

class Piece {
private:
    Piece_type type;
    Color      color;

    int pos_x;
    int pos_y;

    int value;

    bool as_moved{false};

public:
    Piece create(Piece_type piece_type, Color color, int pos_x, int pos_y);

    // The piece move
    void move(int pos_x, int pos_y);
    // The piece is taken and removed from the board
    void remove();
    // Take another piece, return the value of the taken piece
    int take(Piece taken_piece);

    // Get the possible moves of the piece
    std::vector<std::pair<int, int>> get_moves();
};