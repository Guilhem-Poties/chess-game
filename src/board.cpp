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

int Board::coord_to_line(int x, int y)
{
    return x + (y * 8);
}

// Return the piece located at the suggested coordonates and a nullopt if empty
std::optional<Piece> Board::at(int x, int y)
{
    if (is_in_board(x, y))
        return this->_board[coord_to_line(x, y)];
    else
        return std::nullopt;
};

std::optional<Piece> Board::move(int current_x, int current_y, int new_x, int new_y)
{
    if (this->at(new_x, new_y) != std::nullopt)
        take(new_x, new_y);

    this->_board[coord_to_line(new_x, new_y)]         = this->at(current_x, current_y);
    this->_board[coord_to_line(current_x, current_y)] = std::nullopt;
}
std::optional<Piece> Board::take(int x, int y) {}

bool Board::is_in_board(int x, int y)
{
    return (x >= 8 || x < 0 || y >= 8 || y < 0);
}
TILE_STATE Board::tile_state(int x, int y, Color color)
{
    return (this->at(x, y) != std::nullopt ? (this->at(x, y).value().color == color) ? TILE_STATE::ally : TILE_STATE::enemy : TILE_STATE::empty);
}
