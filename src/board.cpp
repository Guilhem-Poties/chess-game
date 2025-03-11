#include "board.hpp"

std::string get_case_written_coordonates(Pos coordonates)
{
    return coordonates_letter[coordonates.y] + std::to_string(coordonates.x + 1);
}

void Board::generate_board()
{
    // this->_board = { {std::make_unique<Tower>(Color::black), std::make_unique<Knight>(Color::white), std::make_unique<Bishop>(Color::white), std::make_unique<King>(Color::white), std::make_unique<Queen>(Color::white), std::make_unique<Bishop>(Color::white), std::make_unique<Knight>(Color::white), std::make_unique<Tower>(Color::white)},
    //                  {std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white), std::make_unique<Pawn>(Color::white)},
    //                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    //                  {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
    // }
    for (size_t pos = 0; pos < 64; pos++)
    {
        this->_board.emplace_back(place_piece(pos));
    }
}

int coord_to_line(Pos pos)
{
    return pos.x + (pos.y * 8);
}
Pos line_to_coord(int l)
{
    return {l % 8, l / 8};
}

// Return the piece located at the suggested coordonates and a nullptr if empty
Piece* Board::at(Pos pos) const
{
    if (is_in_board(pos))
        return this->_board.at(coord_to_line(pos)).get();
    else
        return nullptr;
}

Piece* Board::move(Pos current_pos, Pos new_pos)
{
    Piece* taken_piece{nullptr};

    if (this->at(new_pos) != nullptr)
        taken_piece = take(new_pos);

    this->_board[coord_to_line(new_pos)]     = std::move(this->_board.at(coord_to_line(current_pos)));
    this->_board[coord_to_line(current_pos)] = nullptr;

    return taken_piece;
}
Piece* Board::take(Pos pos)
{
    Piece* captured_piece               = this->at(pos);
    this->_board.at(coord_to_line(pos)) = nullptr;
    return captured_piece;
}

bool Board::is_in_board(Pos pos) const
{
    return ((pos.x >= 0 || pos.x < 8) && (pos.y >= 0 || pos.y < 8));
}
Tile_State Board::tile_state(Pos pos, Color color) const
{
    return (this->at(pos) != nullptr ? (this->at(pos)->get_color() == color) ? Tile_State::ally : Tile_State::enemy : Tile_State::empty);
}