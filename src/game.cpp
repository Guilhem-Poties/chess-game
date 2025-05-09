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
        this->moved_piece = false;
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
        this->moved_piece        = true;

        this->switch_player();

        if (this->promoting = can_promote(this->board, pos))
            this->promotion_pos = pos;

        this->board.calculate_all_moves();

        if (this->board.is_stale_mate(this->current_player))
            std::cout << "Stale mate \n";
        if (this->board.is_checkmate(this->current_player))
            std::cout << "Echec et mat ! \n";
        if (this->board.is_last_move_repeated_position())
            std::cout << "repetition \n";
        // if (this->board.fifty_moves_rule())
        //     std::cout << "fifty \n";
    }

    // Otherwise, nothing happens
};
void Game::end(){
};

void Game::switch_player()
{
    // if (this->get_current_oponant() == Color::white)
    //     std::cout << "white \n";
    // else
    //     std::cout << "black \n";

    this->current_player = this->get_current_oponant();
};
void Game::capture_piece(Piece* piece)
{
    if (piece != nullptr)
    {
        if (this->current_player == Color::white)
            this->captured_pieces.first.push_back(piece);
        else
            this->captured_pieces.second.push_back(piece);
    }
}
void Game::select_piece(Pos pos)
{
    if (auto piece = this->board.at(pos); piece != nullptr)
    {
        this->possible_moves     = this->board.get_piece_move(pos);
        this->selected_piece_pos = pos;
        this->selected_piece     = true;
    }
}

void Game::promote(std::string option)
{
    this->board.promote(this->promotion_pos, this->get_current_oponant(), option);
    this->promoting     = false;
    this->promotion_pos = {};

    this->board.calculate_all_moves();
    if (this->board.is_stale_mate(this->current_player))
        std::cout << "Pat \n";
    if (this->board.is_checkmate(this->current_player))
        std::cout << "Echec et mat ! \n";
    if (this->board.is_last_move_repeated_position())
        std::cout << "Repetition \n";
    if (this->board.fifty_moves_rule())
        std::cout << "fifty \n";
}

bool Game::is_in_move_set(Pos pos)
{
    return std::find(this->possible_moves.begin(), this->possible_moves.end(), pos) != this->possible_moves.end();
}

std::vector<Piece*> Game::get_captured_piece(Color player)
{
    return player == Color::white ? this->captured_pieces.first : this->captured_pieces.second;
}
