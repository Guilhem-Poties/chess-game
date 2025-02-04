#include "game.hpp"

void Game::update(int current_x, int current_y, int new_x, int new_y)
{
    if (std::optional<Piece> piece = this->board.move(current_x, current_y, new_x, new_y); piece != std::nullopt)
        capture_piece(piece.value());

    this->switch_player();
};
void Game::end(){
};

void Game::switch_player()
{
    if (this->current_player == Color::white)
        this->current_player = Color::black;
    else
        this->current_player = Color::white;
};

void Game::capture_piece(Piece piece)
{
    if (this->current_player == Color::white)
        this->captured_pieces.first.push_back(piece);
    else
        this->captured_pieces.second.push_back(piece);
};