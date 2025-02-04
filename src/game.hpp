#include "board.hpp"

#pragma once

class Game {
private:
    Board board{};

    Color current_player{Color::white};
    int   n_turn{0};

    std::pair<float, float> time;
    int                     increment;

    std::pair<std::vector<Piece>, std::vector<Piece>> captured_pieces{{}, {}};

public:
    Game(float _time, int _increment)
        : time(std::make_pair((float)_time, (float)_time)), increment(_increment){};

    void start();
    void update(int current_x, int current_y, int new_x, int new_y);
    void end();

    void switch_player();
    void capture_piece(Piece piece);
};