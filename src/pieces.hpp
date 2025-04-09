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
    virtual std::vector<Pos>       get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) = 0;
    virtual std::unique_ptr<Piece> clone() const                                                           = 0;
    virtual bool                   equal(const Piece& other) const                                         = 0;

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
    std::vector<Pos>               get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) override;
    virtual std::unique_ptr<Piece> clone() const { return std::make_unique<King>(*this); }
    virtual bool                   equal(const Piece& other) const override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Queen : public Piece {
    std::vector<Pos>               get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) override;
    virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Queen>(*this); }
    virtual bool                   equal(const Piece& other) const override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Bishop : public Piece {
    std::vector<Pos>               get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) override;
    virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Bishop>(*this); }
    virtual bool                   equal(const Piece& other) const override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Knight : public Piece {
    std::vector<Pos>               get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) override;
    virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Knight>(*this); }
    virtual bool                   equal(const Piece& other) const override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Tower : public Piece {
    std::vector<Pos>               get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) override;
    virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Tower>(*this); }
    virtual bool                   equal(const Piece& other) const override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

class Pawn : public Piece {
    std::vector<Pos>               get_possible_moves(Board const& board, Pos pos, bool deepsearch = true) override;
    virtual std::unique_ptr<Piece> clone() const { return std::make_unique<Pawn>(*this); }
    virtual bool                   equal(const Piece& other) const override;

    using Piece::Piece;

    const char* to_char();
    std::string to_string();
};

// Place a piece on the board
std::unique_ptr<Piece> place_piece(int pos);

bool can_short_castle(Board const& board, Pos possible_pos, Color king_color);
bool can_long_castle(Board const& board, Pos possible_pos, Color king_color);

bool can_en_passant(Board const& board, Pos pos); // Chack if a piece can do en passant
Pos  get_en_passant_pos(Color pawn_color, Pos pawn_pos);
bool can_promote(Board const& board, Pos pos);

inline operator==(Piece const& piece_a, Piece const& piece_b)
{
    return piece_a.equal(piece_b);
};
inline operator!=(Piece const& piece_a, Piece const& piece_b)
{
    return !(piece_a == piece_b);
};