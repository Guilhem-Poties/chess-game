#include "board.hpp"

std::string get_case_written_coordonates(std::pair<int, int> coordonates)
{
    return coordonates_letter[coordonates.second] + std::to_string(coordonates.first + 1);
}

Board::Board()
{
    // Generate the empty board
    std::vector<std::optional<Piece>> board{};

    for (int _ = 0; _ < 64; _++)
    {
        board.push_back(std::nullopt);
    }

    // Pieces placement
    for (int i = 0; i < 8; i++)
    {
        // board.push_back(Piece((Piece_type)pieces_alignement[i], Color::black, 1, i));
        // board.push_back(Piece(Piece_type::Pawn, Color::black, 1, i));
        // board.push_back(Piece(Piece_type::Pawn, Color::black, 6, i));
        // board.push_back(Piece((Piece_type)pieces_alignement[i], Color::black, 7, i));
    };

    this->_board = board;
};

std::optional<Piece> Board::at(int x, int y)
{
    return this->_board[x + (y * 8)];
};
