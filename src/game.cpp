#include "game.hpp"

void Game::update(Pos pos)
{
    // If the selected piece is the same color as the current player we select this piece
    if (this->board.tile_state(pos, this->current_player) == Tile_State::ally)
    {
        this->select_piece(pos);
    }
    // If the selected case is in the pieces possible moves, we move it and switch players
    else if (this->selected_piece && is_in_move_set(pos))
    {
        if (Piece* piece = this->board.move(this->selected_piece_pos, pos); piece != nullptr)
            capture_piece(piece);

        this->selected_piece     = false;
        this->selected_piece_pos = {};
        this->possible_moves     = {};

        this->switch_player();
    }

    // Otherwise, nothing happens
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
void Game::capture_piece(Piece* piece)
{
    if (this->current_player == Color::white)
        this->captured_pieces.first.push_back(piece);
    else
        this->captured_pieces.second.push_back(piece);
};
void Game::select_piece(Pos pos)
{
    if (auto piece = this->board.at(pos); piece != nullptr)
    {
        this->possible_moves     = piece->get_all_possible_moves(this->board, pos);
        this->selected_piece_pos = pos;
        this->selected_piece     = true;
    }
}

bool Game::is_in_move_set(Pos pos)
{
    return std::find(this->possible_moves.begin(), this->possible_moves.end(), pos) != this->possible_moves.end();
}
