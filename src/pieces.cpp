#include "pieces.hpp"
#include "board.hpp"

// Piece::Piece(Piece_type piece_type, Color piece_color, int piece_pos_x, int piece_pos_y)
// {
//     this->type  = piece_type;
//     this->color = piece_color;
//     this->pos_x = piece_pos_x;
//     this->pos_y = piece_pos_y;
//     this->value = piece_value_by_type[(int)piece_type];
// };

// void Piece::move(int pos_x, int pos_y)
// {
//     this->pos_x = pos_x;
//     this->pos_y = pos_y;
// };

// void Piece::remove()
// {
//     delete this;
// };

// int Piece::take(Piece taken_piece)
// {
//     int taken_value = taken_piece.value;

//     this->move(taken_piece.pos_x, taken_piece.pos_y);

//     taken_piece.remove();
//     return taken_value;
// };

// std::pair<int, int> Piece::get_coordonates()
// {
//     return std::make_pair(this->pos_x, this->pos_y);
// }

// std::vector<std::pair<int, int>> Piece::get_moves()
// {
//     return {};
// }

// King
std::vector<std::pair<int, int>> King::get_all_possible_moves(Board const& board, int x, int y)
{
    std::vector<std::pair<int, int>> all_moves{
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };

    std::vector<std::pair<int, int>> current_possible_moves{};

    for (std::pair<int, int> pair : all_moves)
    {
        int X = x + pair.first;
        int Y = y + pair.second;
        if (board.is_in_board(X, Y) && board.tile_state(X, Y, get_color()) != Tile_State::ally)
        {
            current_possible_moves.emplace_back(X, Y);
        }
    }
}

// Queen
std::vector<std::pair<int, int>> Queen::get_all_possible_moves(Board const& board, int x, int y)
{
    std::vector<std::pair<int, int>> all_moves{
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1},
        {1, 0}
    };

    std::vector<std::pair<int, int>> current_possible_moves{};

    for (std::pair<int, int> pair : all_moves)
    {
        int X = x + pair.first;
        int Y = y + pair.second;
        while (board.is_in_board(X, Y))
        {
            if (board.is_in_board(X, Y) && board.tile_state(X, Y, get_color()) != Tile_State::ally)
            {
                current_possible_moves.emplace_back(X, Y);
                X += pair.first;
                Y += pair.second;
            }
        }
    }
}

// Bishop
std::vector<std::pair<int, int>> Bishop::get_all_possible_moves(Board const& board, int x, int y)
{
    std::vector<std::pair<int, int>> all_moves{
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1}
    };

    std::vector<std::pair<int, int>> current_possible_moves{};

    for (std::pair<int, int> pair : all_moves)
    {
        int X = x + pair.first;
        int Y = y + pair.second;
        if (board.is_in_board(X, Y) && board.tile_state(X, Y, get_color()) != Tile_State::ally)
        {
            current_possible_moves.emplace_back(X, Y);
        }
    }
}

// Knight
std::vector<std::pair<int, int>> Knight::get_all_possible_moves(Board const& board, int x, int y)
{
    std::vector<std::pair<int, int>> all_moves{
        {2, 1},
        {2, -1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {1, -2},
        {-1, -2},
    };

    std::vector<std::pair<int, int>> current_possible_moves{};

    for (std::pair<int, int> pair : all_moves)
    {
        int X = x + pair.first;
        int Y = y + pair.second;
        if (board.is_in_board(X, Y) && board.tile_state(X, Y, get_color()) != Tile_State::ally)
        {
            current_possible_moves.emplace_back(X, Y);
        }
    }
}

// Tower
std::vector<std::pair<int, int>> Tower::get_all_possible_moves(Board const& board, int x, int y)
{
    std::vector<std::pair<int, int>> all_moves{
        {0, 1},
        {-1, 0},
        {0, -1},
        {1, 0}
    };

    std::vector<std::pair<int, int>> current_possible_moves{};

    for (std::pair<int, int> pair : all_moves)
    {
        int X = x + pair.first;
        int Y = y + pair.second;
        if (board.is_in_board(X, Y) && board.tile_state(X, Y, get_color()) != Tile_State::ally)
        {
            current_possible_moves.emplace_back(X, Y);
        }
    }
}

// Pawn
std::vector<std::pair<int, int>> Pawn::get_all_possible_moves(Board const& board, int x, int y)
{
    std::vector<std::pair<int, int>> all_moves{
        {0, 1},
        {0, 2}
    };

    std::vector<std::pair<int, int>> current_possible_moves{};

    for (std::pair<int, int> pair : all_moves)
    {
        int X = x + pair.first;
        int Y = y + pair.second;
        if (board.is_in_board(X, Y) && board.tile_state(X, Y, get_color()) != Tile_State::ally)
        {
            current_possible_moves.emplace_back(X, Y);
        }
    }
}
