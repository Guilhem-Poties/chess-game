#include "board.hpp"

#pragma once

class Game {
private:
    Color current_player{Color::white};
    int   n_turn{0};

    std::pair<float, float> time;
    int                     increment;

    bool                                              selected_piece{false};
    std::pair<int, int>                               selected_piece_pos{};
    std::vector<std::pair<int, int>>                  possible_moves{};
    std::pair<std::vector<Piece>, std::vector<Piece>> captured_pieces{{}, {}};

public:
    Board board{};
    Game(float _time, int _increment)
        : time(std::make_pair((float)_time, (float)_time)), increment(_increment){};

    void start();
    void update(int x, int y);
    void end();

    void switch_player();
    void capture_piece(Piece piece);
    void select_piece(int x, int y);
};