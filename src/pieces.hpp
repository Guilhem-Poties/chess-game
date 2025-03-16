#pragma once
#include <cstddef>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Board;
struct Pos;

#ifndef PIECES_ATTRIBUTES

const std::vector<int> pieces_alignement{3, 1, 2, 0, 4, 2, 1, 3};
#endif

enum class Color : int {
    black,
    white
};

class Piece {
public:
    virtual std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) = 0;

    Color get_color() const { return color; }
    bool  has_moved() const { return this->moved; }
    void  moved_piece() { this->moved = true; }

    Piece(Color c)
        : color(c)
    {}

    virtual const char* to_char();
    virtual std::string to_string();

private:
    Color color;
    bool  moved{false};
    int   value;
};

// enum class Direction{
//     Left,Right,

// }

class King : public Piece {
    std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Queen : public Piece {
    std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Bishop : public Piece {
    std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Knight : public Piece {
    std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Tower : public Piece {
    std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Pawn : public Piece {
    std::vector<Pos> get_all_possible_moves(Board const& board, Pos pos) override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

std::unique_ptr<Piece> place_piece(int pos);
bool                   can_en_passant(Board const& board, Pos pos);

// enum class Piece_type : int {
//     Queen,
//     Tower,
//     Bishop,
//     Knight,
//     Pawn,
//     King
// };

// class Piece {
// private:
//     int pos_x{};
//     int pos_y{};

//     int value;

//     bool as_moved{false};

// public:
//     Piece_type type{};
//     Color      color{};

//     Piece(Piece_type piece_type, Color color, int pos_x, int pos_y);

//     // The piece move
//     void move(int pos_x, int pos_y);
//     // The piece is taken and removed from the board
//     void remove();
//     // Take another piece, return the value of the taken piece
//     int take(Piece taken_piece);

//     std::pair<int, int> get_coordonates();

//     // Get the possible moves of the piece
//     std::vector<std::pair<int, int>> get_moves();
// };