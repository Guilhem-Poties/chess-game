#include "board.hpp"

#pragma once

class Game {
private:
    Color current_player{Color::white};
    int   n_turn{0};

    std::pair<float, float> time;
    int                     increment;

    bool                                                selected_piece{false};
    Pos                                                 selected_piece_pos{};
    std::vector<Pos>                                    possible_moves{};
    std::pair<std::vector<Piece*>, std::vector<Piece*>> captured_pieces{{}, {}};
    std::vector<std::pair<Piece*, Pos>>                 move_history{};

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
};