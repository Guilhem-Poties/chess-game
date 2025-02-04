#include "board.hpp"

std::string get_case_written_coordonates(std::pair<int, int> coordonates)
{
    return coordonates_letter[coordonates.second] + std::to_string(coordonates.first + 1);
}

Board::Board()
{
    // Generate the empty board
    std::vector<Piece> pieces{};

    // Pieces placement
    for (int i = 0; i < 8; i++)
    {
        pieces.push_back(Piece((Piece_type)pieces_alignement[i], Color::black, 1, i));
        pieces.push_back(Piece(Piece_type::Pawn, Color::black, 1, i));
        pieces.push_back(Piece(Piece_type::Pawn, Color::black, 6, i));
        pieces.push_back(Piece((Piece_type)pieces_alignement[i], Color::black, 7, i));
    };

    this->pieces = pieces;
}

Piece Board::at(int pos_x, int pos_y)
{
    //     auto const same_coordonates = [&](Piece& piece) {
    //     return piece.get_coordonates().first == pos_x && piece.get_coordonates().second == pos_y;
    // };

    // if (auto it = std::find(pieces.begin(), pieces.end(), same_coordonates) == pieces.end())
    //     return pieces[it];
    // else
    // {
    //     throw errno;
    //     return pieces[0];
    // }
}

int Board::n_piece()
{
    return this->pieces.size();
}