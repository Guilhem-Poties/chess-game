#include "pieces.hpp"
#include "board.hpp"

const char* Piece::to_char()
{
    return " ";
}
std::string Piece::to_string()
{
    return " ";
}

// King
std::vector<Pos> King::get_possible_moves(Board const& board, Pos pos, bool deepsearch)
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
        Pos move = pos + pos_add;

        if (board.is_in_board(move) && board.tile_state(move, this->get_color()) != Tile_State::ally && (!deepsearch || !board.is_move_future_check(pos, move, this->get_color())))
            current_possible_moves.emplace_back(move);
    }

    return current_possible_moves;
}
const char* King::to_char()
{
    return "l";
}
std::string King::to_string()
{
    return "King";
}

// Queen
std::vector<Pos> Queen::get_possible_moves(Board const& board, Pos pos, bool deepsearch)
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
        Pos move = pos + pos_add;
        while (board.is_in_board(move) && board.tile_state(move, get_color()) != Tile_State::ally)
        {
            if (!deepsearch || !board.is_move_future_check(pos, move, this->get_color()))
                current_possible_moves.emplace_back(move);
            if (board.tile_state(move, get_color()) == Tile_State::enemy)
                break;
            move = move + pos_add;
        }
    }
    return current_possible_moves;
}
const char* Queen::to_char()
{
    return "w";
}
std::string Queen::to_string()
{
    return "Queen";
}

// Bishop
std::vector<Pos> Bishop::get_possible_moves(Board const& board, Pos pos, bool deepsearch)
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
        Pos move = pos + pos_add;
        while (board.is_in_board(move) && board.tile_state(move, get_color()) != Tile_State::ally)
        {
            if ((!deepsearch || !board.is_move_future_check(pos, move, this->get_color())))
                current_possible_moves.emplace_back(move);
            if (board.tile_state(move, get_color()) == Tile_State::enemy)
                break;
            move = move + pos_add;
        }
    }
    return current_possible_moves;
}
const char* Bishop::to_char()
{
    return "n";
}
std::string Bishop::to_string()
{
    return "Bishop";
}

// Knight
std::vector<Pos> Knight::get_possible_moves(Board const& board, Pos pos, bool deepsearch)
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
        Pos move = pos + pos_add;

        if (board.is_in_board(move))
        {
            if (board.tile_state(move, get_color()) != Tile_State::ally && (!deepsearch || !board.is_move_future_check(pos, move, this->get_color())))
                current_possible_moves.emplace_back(move);
        }
    }
    return current_possible_moves;
}
const char* Knight::to_char()
{
    return "j";
}
std::string Knight::to_string()
{
    return "Knight";
}

// Tower
std::vector<Pos> Tower::get_possible_moves(Board const& board, Pos pos, bool deepsearch)
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
        Pos move = pos + pos_add;
        while (board.is_in_board(move) && board.tile_state(move, get_color()) != Tile_State::ally)
        {
            if ((!deepsearch || !board.is_move_future_check(pos, move, this->get_color())))
                current_possible_moves.emplace_back(move);
            if (board.tile_state(move, get_color()) == Tile_State::enemy)
                break;
            move = move + pos_add;
        }
    }
    return current_possible_moves;
}
const char* Tower::to_char()
{
    return "t";
}
std::string Tower::to_string()
{
    return "Tower";
}

// Pawn
std::vector<Pos> Pawn::get_possible_moves(Board const& board, Pos pos, bool deepsearch)
{
    std::vector<Pos> all_moves{{0, 1}};
    std::vector<Pos> all_attacks{
        {1, 1},
        {-1, 1}
    };
    std::vector<Pos> current_possible_moves{};

    // If the pawn hasn't moved yet, he wan move on a additionnal square
    if (!this->has_moved() && (board.tile_state(get_en_passant_pos(this->get_color(), pos), this->get_color()) != Tile_State::empty))
        all_moves.push_back({0, 2});

    for (Pos pos_add : all_moves)
    {
        Pos move = this->get_color() == Color::white ? pos + pos_add : pos - pos_add;

        if (board.is_in_board(move) && board.tile_state(move, get_color()) == Tile_State::empty && (!deepsearch || !board.is_move_future_check(pos, move, this->get_color())))
        {
            current_possible_moves.emplace_back(move);
        }
    }

    for (Pos pos_add : all_attacks)
    {
        Pos move = this->get_color() == Color::white ? pos + pos_add : pos - pos_add;

        // Calulate wether the an passant should be depending of the pawn color/direction
        Pos en_passant_pos{get_en_passant_pos(this->get_color(), move)};

        if (board.is_in_board(move) && (board.tile_state(move, this->get_color()) == Tile_State::enemy || can_en_passant(board, en_passant_pos)) && (!deepsearch || !board.is_move_future_check(pos, move, this->get_color())))
        {
            current_possible_moves.emplace_back(move);
        }
    }
    return current_possible_moves;
}
const char* Pawn::to_char()
{
    return "o";
}
std::string Pawn::to_string()
{
    return "Pawn";
}

std::unique_ptr<Piece> place_piece(int pos)
{
    if (int y = line_to_pos(pos).y; y == 0)
    {
        switch (pieces_alignement[line_to_pos(pos).x])
        {
        case 3:
            return std::make_unique<Tower>(Color::white);
        case 1:
            return std::make_unique<Knight>(Color::white);
        case 2:
            return std::make_unique<Bishop>(Color::white);
        case 0:
            return std::make_unique<King>(Color::white);
        case 4:
            return std::make_unique<Queen>(Color::white);
        default:
            return nullptr;
        }
    }
    else if (y == 7)
    {
        switch (pieces_alignement[line_to_pos(pos).x])
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

    // if (pos == 1)
    //     return std::make_unique<King>(Color::black);
    // else if (pos == 15)
    //     return std::make_unique<Tower>(Color::white);
    // else if (pos == 14)
    //     return std::make_unique<Tower>(Color::white);
    // else if (pos == 63)
    //     return std::make_unique<King>(Color::white);
    // else if (pos == 27)
    //     return std::make_unique<Queen>(Color::black);

    else
        return nullptr;
}

// Take the board and the pos where there would might be a pawn to take en passant
bool can_en_passant(Board const& board, Pos pos)
{
    if (board.get_last_move().has_value())
    {
        std::pair<Piece*, std::pair<Pos, Pos>> last_move{board.get_last_move().value()};
        if (dynamic_cast<Pawn*>(last_move.first))
        {
            if (last_move.second.first.y == last_move.second.second.y - 2 || last_move.second.first.y == last_move.second.second.y + 2)
            {
                return board.at(pos) == last_move.first;
            }
            else
                return false;
        }
        else
            return false;
    }
    else
        return false;

    // return board.get_last_move().has_value() && (dynamic_cast<Pawn*>(board.get_last_move().value().first) && board.at(pos) == board.get_last_move().value().first) && board.get_last_move().value().second.first;
}
// Take a move and decide the direction of the en passant position depnding on the color
Pos get_en_passant_pos(Color pawn_color, Pos pawn_pos)
{
    return pawn_color == Color::white ? pawn_pos.incr_y(-1) : pawn_pos.incr_y(1);
}