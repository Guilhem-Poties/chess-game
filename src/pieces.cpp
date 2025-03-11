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

// Pos Piece::get_coordonates()
// {
//     return std::make_pos_add(this->pos_x, this->pos_y);
// }

// std::vector<Pos> Piece::get_moves()
// {
//     return {};
// }

char Piece::to_char()
{
    return ' ';
}
std::string Piece::to_string()
{
    return " ";
}

// King
std::vector<Pos> King::get_all_possible_moves(Board const& board, Pos pos)
{
    std::vector<Pos> all_moves{
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1}
    };

    std::vector<Pos> current_possible_moves{};

    for (Pos pos_add : all_moves)
    {
        Pos move = {pos.x + pos_add.x, pos.y + pos_add.y};

        if (board.is_in_board(move))
        {
            if (board.tile_state(move, get_color()) != Tile_State::ally)
            {
                current_possible_moves.emplace_back(move);
            }
        }
    }
    return current_possible_moves;
}
char King::to_char()
{
    return 'k';
}
std::string King::to_string()
{
    return "King";
}

// Queen
std::vector<Pos> Queen::get_all_possible_moves(Board const& board, Pos pos)
{
    std::vector<Pos> all_moves{
        {1, 1},
        {0, 1},
        {-1, 1},
        {-1, 0},
        {-1, -1},
        {0, -1},
        {1, -1},
        {1, 0}
    };

    std::vector<Pos> current_possible_moves{};

    for (Pos pos_add : all_moves)
    {
        Pos move = {pos.x + pos_add.x, pos.y + pos_add.y};
        while (board.is_in_board(move))
        {
            if (board.is_in_board(move))
            {
                if (board.tile_state(move, get_color()) != Tile_State::ally)
                {
                    current_possible_moves.emplace_back(move);
                    move = move + pos_add;
                }
            }
        }
    }
    return current_possible_moves;
}
char Queen::to_char()
{
    return 'q';
}
std::string Queen::to_string()
{
    return "Queen";
}

// Bishop
std::vector<Pos> Bishop::get_all_possible_moves(Board const& board, Pos pos)
{
    std::vector<Pos> all_moves{
        {1, 1},
        {-1, 1},
        {-1, -1},
        {1, -1}
    };

    std::vector<Pos> current_possible_moves{};

    for (Pos pos_add : all_moves)
    {
        Pos move = {pos.x + pos_add.x, pos.y + pos_add.y};

        if (board.is_in_board(move))
        {
            if (board.tile_state(move, get_color()) != Tile_State::ally)
            {
                current_possible_moves.emplace_back(move);
            }
        }
    }
    return current_possible_moves;
}
char Bishop::to_char()
{
    return 'b';
}
std::string Bishop::to_string()
{
    return "Bishop";
}

// Knight
std::vector<Pos> Knight::get_all_possible_moves(Board const& board, Pos pos)
{
    std::vector<Pos> all_moves{
        {2, 1},
        {2, -1},
        {1, 2},
        {-1, 2},
        {-2, 1},
        {-2, -1},
        {1, -2},
        {-1, -2},
    };

    std::vector<Pos> current_possible_moves{};

    for (Pos pos_add : all_moves)
    {
        Pos move = {pos.x + pos_add.x, pos.y + pos_add.y};

        if (board.is_in_board(move))
        {
            if (board.tile_state(move, get_color()) != Tile_State::ally)
            {
                current_possible_moves.emplace_back(move);
            }
        }
    }
    return current_possible_moves;
}
char Knight::to_char()
{
    return 'c';
}
std::string Knight::to_string()
{
    return "Knight";
}

// Tower
std::vector<Pos> Tower::get_all_possible_moves(Board const& board, Pos pos)
{
    std::vector<Pos> all_moves{
        {0, 1},
        {-1, 0},
        {0, -1},
        {1, 0}
    };

    std::vector<Pos> current_possible_moves{};

    for (Pos pos_add : all_moves)
    {
        Pos move = {pos.x + pos_add.x, pos.y + pos_add.y};

        if (board.is_in_board(move))
        {
            if (board.tile_state(move, get_color()) != Tile_State::ally)
            {
                current_possible_moves.emplace_back(move);
            }
        }
    }
    return current_possible_moves;
}
char Tower::to_char()
{
    return 't';
}
std::string Tower::to_string()
{
    return "Tower";
}

// Pawn
std::vector<Pos> Pawn::get_all_possible_moves(Board const& board, Pos pos)
{
    std::vector<Pos> all_moves{{0, 1}};
    std::vector<Pos> current_possible_moves{};

    if (!this->has_moved())
        all_moves.push_back({0, 2});

    for (Pos pos_add : all_moves)
    {
        Pos move = this->get_color() == Color::white ? pos + pos_add : pos - pos_add;

        if (board.is_in_board(move) && board.tile_state(move, get_color()) != Tile_State::ally)
        {
            current_possible_moves.emplace_back(move);
        }
    }
    return current_possible_moves;
}
char Pawn::to_char()
{
    return 'p';
}
std::string Pawn::to_string()
{
    return "Pawn";
}

std::unique_ptr<Piece> place_piece(int pos)
{
    if (int y = line_to_coord(pos).y; y == 0)
    {
        switch (pieces_alignement[line_to_coord(pos).x])
        {
        case 3:
            return std::make_unique<Tower>(Color::black);
        case 1:
            return std::make_unique<Knight>(Color::black);
        case 2:
            return std::make_unique<Bishop>(Color::black);
        case 0:
            return std::make_unique<King>(Color::black);
        case 4:
            return std::make_unique<Queen>(Color::black);
        default:
            return nullptr;
        }
    }
    else if (y == 7)
    {
        switch (pieces_alignement[line_to_coord(pos).x])
        {
        case 3:
            return std::make_unique<Tower>(Color::black);
        case 1:
            return std::make_unique<Knight>(Color::black);
        case 2:
            return std::make_unique<Bishop>(Color::black);
        case 0:
            return std::make_unique<King>(Color::black);
        case 4:
            return std::make_unique<Queen>(Color::black);
        default:
            return nullptr;
        }
    }
    else if (y == 1)
        return std::make_unique<Pawn>(Color::white);
    else if (y == 6)
        return std::make_unique<Pawn>(Color::black);
    else
        return nullptr;
}