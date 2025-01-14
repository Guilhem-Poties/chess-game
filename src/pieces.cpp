#include "pieces.hpp"

Piece Piece::create(Piece_type piece_type, Color color, int pos_x, int pos_y)
{
    Piece piece{piece_type, color, pos_x, pos_y, piece_value_by_type[(int)piece_type]};

    return piece
};

void Piece::move(int pos_x, int pos_y)
{
    this->pos_x = pos_x;
    this->pos_y = pos_y;
};

void Piece::remove()
{
    delete this;
};

int Piece::take(Piece taken_piece)
{
    int taken_value = taken_piece.value;

    this->move(taken_piece.pos_x, taken_piece.pos_y);

    taken_piece.remove();
    return taken_value;
};