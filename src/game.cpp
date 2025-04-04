#include "game.hpp"

void Game::start()
{
    this->board.generate_board();
    this->board.calculate_all_moves();
}
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
        // If there an en passant take is possible from this move, it means that the player has selected it
        bool en_passant{can_en_passant(this->board, get_en_passant_pos(this->board.at(this->selected_piece_pos)->get_color(), pos))};
        bool short_castle{can_short_castle(this->board, pos, this->board.at(this->selected_piece_pos)->get_color())};
        bool long_castle{can_long_castle(this->board, pos, this->board.at(this->selected_piece_pos)->get_color())};

        capture_piece(this->board.move(this->selected_piece_pos, pos, en_passant, short_castle, long_castle));

        // Reset the variables and mention that the piece has been moved
        this->board.at(pos)->moved_piece();
        this->selected_piece     = false;
        this->selected_piece_pos = {};
        this->possible_moves     = {};

        this->switch_player();

        this->board.calculate_all_moves();

        if (this->board.is_check(this->current_player))
            std::cout << "Echec ! \n";
        if (this->board.is_stale_mate(this->current_player))
            std::cout << "Stale mate \n";
        if (this->board.is_checkmate(this->current_player))
            std::cout << "Echec et mat ! \n";
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
    if (piece == nullptr)
    {
        if (this->current_player == Color::white)
            this->captured_pieces.first.push_back(piece);
        else
            this->captured_pieces.second.push_back(piece);
    }
};
void Game::select_piece(Pos pos)
{
    if (auto piece = this->board.at(pos); piece != nullptr)
    {
        this->possible_moves     = this->board.get_piece_move(pos);
        this->selected_piece_pos = pos;
        this->selected_piece     = true;
    }
}

bool Game::is_in_move_set(Pos pos)
{
    return std::find(this->possible_moves.begin(), this->possible_moves.end(), pos) != this->possible_moves.end();
}
