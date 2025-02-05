#include "pieces.hpp"

Piece::Piece(Piece_type piece_type, Color piece_color, int piece_pos_x, int piece_pos_y)
{
    this->type  = piece_type;
    this->color = piece_color;
    this->pos_x = piece_pos_x;
    this->pos_y = piece_pos_y;
    this->value = piece_value_by_type[(int)piece_type];
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

std::pair<int, int> Piece::get_coordonates()
{
    return std::make_pair(this->pos_x, this->pos_y);
}

std::vector<std::pair<int, int>> Piece::get_moves()
{
    return {};
}