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

        if (board.is_in_board(move) && board.tile_state(move, this->get_color()) != Tile_State::ally && (!deepsearch || !board.is_move_future_check(pos, move)))
            current_possible_moves.emplace_back(move);
    }

    if (deepsearch && can_short_castle(board, pos.incr_x(-2), this->get_color()))
        current_possible_moves.push_back(pos.incr_x(-2));
    if (deepsearch && can_long_castle(board, pos.incr_x(2), this->get_color()))
        current_possible_moves.push_back(pos.incr_x(2));

    return current_possible_moves;
}
bool King::equal(const Piece& other) const
{
    const King* other_piece = dynamic_cast<const King*>(&other);
    return other_piece && this->get_color() == other_piece->get_color();
}
const char* King::to_char()
{
    return "l";
}
std::string King::to_string()
{
    return "king";
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
            if (!deepsearch || !board.is_move_future_check(pos, move))
                current_possible_moves.emplace_back(move);
            if (board.tile_state(move, get_color()) == Tile_State::enemy)
                break;
            move += pos_add;
        }
    }
    return current_possible_moves;
}
bool Queen::equal(const Piece& other) const
{
    const Queen* other_piece = dynamic_cast<const Queen*>(&other);
    return other_piece && this->get_color() == other_piece->get_color();
}
const char* Queen::to_char()
{
    return "w";
}
std::string Queen::to_string()
{
    return "queen";
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
            if ((!deepsearch || !board.is_move_future_check(pos, move)))
                current_possible_moves.emplace_back(move);
            if (board.tile_state(move, get_color()) == Tile_State::enemy)
                break;
            move += pos_add;
        }
    }
    return current_possible_moves;
}
bool Bishop::equal(const Piece& other) const
{
    const Bishop* other_piece = dynamic_cast<const Bishop*>(&other);
    return other_piece && this->get_color() == other_piece->get_color();
}
const char* Bishop::to_char()
{
    return "n";
}
std::string Bishop::to_string()
{
    return "bishop";
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
            if (board.tile_state(move, get_color()) != Tile_State::ally && (!deepsearch || !board.is_move_future_check(pos, move)))
                current_possible_moves.emplace_back(move);
    }
    return current_possible_moves;
}
const char* Knight::to_char()
{
    return "j";
}
std::string Knight::to_string()
{
    return "knight";
}
bool Knight::equal(const Piece& other) const
{
    const Knight* other_piece = dynamic_cast<const Knight*>(&other);
    return other_piece && this->get_color() == other_piece->get_color();
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
            if ((!deepsearch || !board.is_move_future_check(pos, move)))
                current_possible_moves.emplace_back(move);
            if (board.tile_state(move, get_color()) == Tile_State::enemy)
                break;
            move += pos_add;
        }
    }
    return current_possible_moves;
}
bool Tower::equal(const Piece& other) const
{
    const Tower* other_piece = dynamic_cast<const Tower*>(&other);
    return other_piece && this->get_color() == other_piece->get_color();
}
const char* Tower::to_char()
{
    return "t";
}
std::string Tower::to_string()
{
    return "tower";
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
    if (!this->has_moved() && (board.tile_state(Color::white == this->get_color() ? pos.incr_y(1) : pos.incr_y(-1), this->get_color()) == Tile_State::empty))
        all_moves.push_back({0, 2});

    for (Pos pos_add : all_moves)
    {
        Pos move = this->get_color() == Color::white ? pos + pos_add : pos - pos_add;

        if (board.is_in_board(move) && board.tile_state(move, get_color()) == Tile_State::empty && (!deepsearch || !board.is_move_future_check(pos, move)))
            current_possible_moves.emplace_back(move);
    }

    for (Pos pos_add : all_attacks)
    {
        Pos move = this->get_color() == Color::white ? pos + pos_add : pos - pos_add;

        // Calulate wether the an passant should be depending of the pawn color/direction
        Pos en_passant_pos{get_en_passant_pos(this->get_color(), move)};

        if (board.is_in_board(move) && (board.tile_state(move, this->get_color()) == Tile_State::enemy || can_en_passant(board, en_passant_pos)) && (!deepsearch || !board.is_move_future_check(pos, move)))
            current_possible_moves.emplace_back(move);
    }
    return current_possible_moves;
}
bool Pawn::equal(const Piece& other) const
{
    const Pawn* other_piece = dynamic_cast<const Pawn*>(&other);
    return other_piece && this->get_color() == other_piece->get_color();
}
const char* Pawn::to_char()
{
    return "o";
}
std::string Pawn::to_string()
{
    return "pawn";
}

std::unique_ptr<Piece> place_piece(int pos)
{
    switch (line_to_pos(pos).y)
    {
    case 0:

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

    case 7:
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

    case 1:
        return std::make_unique<Pawn>(Color::white);
    case 6:
        return std::make_unique<Pawn>(Color::black);
    default:
        return nullptr;
    }

    // if (pos == 3)
    //     return std::make_unique<King>(Color::white);
    // else if (pos == 0)
    //     return std::make_unique<Tower>(Color::white);
    // else if (pos == 7)
    //     return std::make_unique<Tower>(Color::white);
    // else if (pos == 6)
    //     return std::make_unique<Tower>(Color::white);
    // else if (pos == 58)
    //     return std::make_unique<Tower>(Color::black);
    // else if (pos == 63)
    //     return std::make_unique<King>(Color::black);
}

bool can_short_castle(Board const& board, Pos possible_pos, Color king_color)
{
    auto king_pos{possible_pos.incr_x(2)};
    auto tower_pos{possible_pos.incr_x(-1)};
    auto king{board.at(king_pos)};
    auto tower{board.at(tower_pos)};

    if (board.is_king(king_color, king_pos) && board.is_tower(king_color, tower_pos) && !king->has_moved() && !tower->has_moved())
    {
        std::vector<Pos> range{king_pos.incr_x(-1), possible_pos};
        if (std::find_if(range.begin(), range.end(), [&board, king_color](Pos pos) { return board.tile_state(pos, king_color) != Tile_State::empty; }) == range.end())
        {
            range.push_back(king_pos);
            return std::find_if(range.begin(), range.end(), [&board, king_pos](Pos pos) { return board.is_move_future_check(king_pos, pos); }) == range.end();
        }
        else
            return false;
    }
    else
        return false;
}
bool can_long_castle(Board const& board, Pos possible_pos, Color king_color)
{
    auto king_pos{possible_pos.incr_x(-2)};
    auto tower_pos{possible_pos.incr_x(2)};
    auto king{board.at(king_pos)};
    auto tower{board.at(tower_pos)};

    if (board.is_king(king_color, king_pos) && board.is_tower(king_color, tower_pos) && !king->has_moved() && !tower->has_moved())
    {
        std::vector<Pos> range{king_pos.incr_x(1), possible_pos, possible_pos.incr_x(1)};
        if (std::find_if(range.begin(), range.end(), [&board, king_color](Pos pos) { return board.tile_state(pos, king_color) != Tile_State::empty; }) == range.end())
        {
            range.pop_back();
            range.push_back(king_pos);
            return std::find_if(range.begin(), range.end(), [&board, king_pos](Pos pos) { return board.is_move_future_check(king_pos, pos); }) == range.end();
        }
        else
            return false;
    }
    else
        return false;
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