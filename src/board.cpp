#include "board.hpp"

std::string get_case_written_coordonates(std::pair<int, int> coordonates)
{
    return coordonates_letter[coordonates.second] + std::to_string(coordonates.first + 1);
}

void Board::generate_board()
{
    for (int _ = 0; _ < 64; _++)
    {
        this->_board.push_back(Piece(Piece_type::Pawn, Color::black, 1, 1));
    }

    // // Pieces placement
    // for (int i = 0; i < 8; i++)
    // {
    //     std::cout << "ouiiiii";
    //     board[8 + i]  = (Piece(Piece_type::Pawn, Color::black, 1, i));
    //     board[48 + i] = (Piece(Piece_type::Pawn, Color::black, 6, i));
    //     board[56 + i] = (Piece((Piece_type)pieces_alignement[i], Color::black, 7, i));
    // };
}

int coord_to_line(int x, int y)
{
    return x + (y * 8);
}
std::pair<int, int> line_to_coord(int l)
{
    return std::make_pair(l / 8, l % 8);
}

// Return the piece located at the suggested coordonates and a nullopt if empty
std::optional<Piece> Board::at(int x, int y)
{
    if (is_in_board(x, y))
        return this->_board[coord_to_line(x, y)];
    else
        return std::nullopt;
}

std::optional<Piece> Board::move(int current_x, int current_y, int new_x, int new_y)
{
    std::optional<Piece> taken_piece{std::nullopt};

    if (this->at(new_x, new_y) != std::nullopt)
        taken_piece = take(new_x, new_y);

    this->_board[coord_to_line(new_x, new_y)]         = this->at(current_x, current_y);
    this->_board[coord_to_line(current_x, current_y)] = std::nullopt;

    return taken_piece;
}
std::optional<Piece> Board::take(int x, int y)
{
    return this->at(x, y);
}

bool Board::is_in_board(int x, int y) const
{
    return (x >= 0 || x < 8 || y >= 0 || y < 8);
}
Tile_State Board::tile_state(int x, int y, Color color) const
{
    return (this->at(x, y) != std::nullopt ? (this->at(x, y).value().color == color) ? Tile_State::ally : Tile_State::enemy : Tile_State::empty);
}