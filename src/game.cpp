#include "game.hpp"

void Game::update(int x, int y)
{
    if (this->selected_piece)
    {
        if (this->board.tile_state(x, y, this->current_player) == Tile_State::ally)
        {
            this->select_piece(x, y);
        }
        else
        {
            if (std::optional<Piece> piece = this->board.move(this->selected_piece_pos.first, this->selected_piece_pos.second, x, y); piece != std::nullopt)
                capture_piece(piece.value());

            this->selected_piece     = false;
            this->selected_piece_pos = {};
            this->possible_moves     = {};
        }
    }
    else
    {
        select_piece(x, y);
    }

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
void Game::select_piece(int x, int y)
{
    if (auto piece = this->board.at(x, y); piece != std::nullopt)
    {
        this->possible_moves     = piece.value().get_moves();
        this->selected_piece_pos = std::make_pair(x, y);
        this->selected_piece     = true;
    }
}
