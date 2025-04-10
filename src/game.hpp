#include "board.hpp"

#pragma once

class Game {
private:
    Color current_player{Color::white};

    std::pair<float, float> time;
    int                     increment;

    bool promoting = false;
    Pos  promotion_pos;

    bool                                                selected_piece{false};
    Pos                                                 selected_piece_pos{};
    std::vector<Pos>                                    possible_moves{};
    std::pair<std::vector<Piece*>, std::vector<Piece*>> captured_pieces;
    bool                                                moved_piece = false; // Définit si une pièce a été jouée au denier update

public:
    Board board{};
    Game(float _time, int _increment)
        : time(std::make_pair((float)_time, (float)_time)), increment(_increment){};

    void start();
    void update(Pos pos);
    void end();

    void switch_player();
    void capture_piece(Piece* piece);
    void select_piece(Pos pos);

    bool is_in_move_set(Pos pos);

    bool is_promoting() { return this->promoting; };
    void promote(std::string option);

    Color               get_current_oponant() const { return (Color)((((int)this->current_player) + 1) % 2); };
    std::vector<Piece*> get_captured_piece(Color player);

    bool has_moved_piece() { return this->moved_piece; };
    void unmove_piece() { this->moved_piece = false; };
};