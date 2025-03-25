#include "board.hpp"
void Board::generate_board()
{
    for (size_t pos = 0; pos < 64; pos++)
    {
        this->_board.emplace_back(place_piece(pos));
    }
}
int Board::n_turns_played() const
{
    return this->move_history.size();
}

/****** Piece managment functions ******/

// Return the piece located at the suggested coordonates and a nullptr if empty
Piece* Board::at(Pos pos) const
{
    if (is_in_board(pos))
        return this->_board.at(pos_to_line(pos)).get();
    else
        return nullptr;
}

std::optional<Piece*> Board::move(Pos current_pos, Pos new_pos, bool en_passant)
{
    this->move_history.push_back(std::make_pair(this->at(current_pos), std::make_pair(current_pos, new_pos)));

    Piece* captured_piece{this->at(new_pos)};

    if (en_passant)
    {
        captured_piece = this->at(get_en_passant_pos(this->at(current_pos)->get_color(), new_pos));

        this->_board[pos_to_line(get_en_passant_pos(this->at(current_pos)->get_color(), new_pos))] = nullptr;
    }

    this->_board[pos_to_line(new_pos)]     = std::move(this->_board.at(pos_to_line(current_pos)));
    this->_board[pos_to_line(current_pos)] = nullptr;

    return captured_piece;
}

void Board::calculate_all_moves()
{
    std::vector<std::vector<Pos>> all_adjusted_moves{};

    // this->all_moves = {};
    for (size_t i = 0; i < this->_board.size(); i++)
    {
        if (Piece* piece = this->at(line_to_pos(i)); piece != nullptr)
            all_adjusted_moves.push_back(piece->get_possible_moves(*this, line_to_pos(i)));
        else
            all_adjusted_moves.push_back({});
    }

    if (this->all_moves != all_adjusted_moves)
    {
        this->all_moves = all_adjusted_moves;
        this->calculate_all_moves();
    }
    this->is_king_attacked(this->king_pos(Color::white), Color::white);
}
void Board::reset_all_moves()
{
    this->all_moves = {};
    this->calculate_all_moves();
}
std::optional<std::pair<Piece*, std::pair<Pos, Pos>>> Board::get_last_move() const
{
    if (this->move_history.size() != 0)
        return this->move_history.back();
    else
        return std::nullopt;
}
std::vector<Pos> Board::get_piece_move(Pos pos) const
{
    return this->all_moves.at(pos_to_line(pos));
}

/****** Check managment functions ******/

Pos Board::king_pos(Color king_color)
{
    auto is_king = [king_color](const std::unique_ptr<Piece>& piece) {
        return piece != nullptr && piece.get()->get_color() == king_color && dynamic_cast<King*>(piece.get());
    };

    if (auto king_pos{std::find_if(this->_board.begin(), this->_board.end(), is_king)}; king_pos != this->_board.end())
        return line_to_pos(std::distance(this->_board.begin(), king_pos));
    else
        return {-1, -1};
}
std::vector<std::vector<Pos>> Board::is_king_attacked(Pos king_pos, Color king_color)
{
    // Takes the same scheme as the queen movments but cheks if the piece is attacking
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

    std::vector<std::vector<Pos>> attaking_pieces{};

    for (Pos move_add : all_moves)
    {
        std::vector<Pos> move_stack = {};    // Stack all the moves between a piece and the attacker and the king
        bool             pined_piece{false}; // Pin a piece if she's the only one in the way
        Pos              pined_piece_pos{};
        bool             first_ally_encountered{true}; // Checks if an ally piece is the first one encountered in order to pin it if it is

        Pos move = king_pos + move_add;
        while (this->is_in_board(move))
        {
            if (first_ally_encountered && this->tile_state(move, king_color) == Tile_State::ally)
            {
                pined_piece            = true;
                pined_piece_pos        = move;
                first_ally_encountered = false;
            }
            else if (this->tile_state(move, king_color) == Tile_State::ally)
                pined_piece = false;
            else if (this->tile_state(move, king_color) == Tile_State::enemy)
            {
                if (pined_piece)
                    this->at(pined_piece_pos)->pin_piece();
                else
                    attaking_pieces.push_back(move_stack);

                break;
            }

            move_stack.push_back(move);
            move = move + move_add;
        }
    }

    return attaking_pieces;
}
bool Board::is_move_in_enemy_range(Pos move, Color color) const
{
    for (size_t i{0}; i < this->all_moves.size(); i++)
    {
        if (this->tile_state(line_to_pos(i), color) == Tile_State::enemy)
        {
            if (std::find(this->all_moves.at(i).begin(), this->all_moves.at(i).end(), move) != this->all_moves.at(i).end())
                return true;
        }
    }
    return false;
}

/****** Tile status managment ******/

bool Board::is_in_board(Pos pos) const
{
    return ((pos.x >= 0 && pos.x < 8) && (pos.y >= 0 && pos.y < 8));
}
Tile_State Board::tile_state(Pos pos, Color color) const
{
    return (this->at(pos) != nullptr ? ((this->at(pos)->get_color() == color) ? Tile_State::ally : Tile_State::enemy) : Tile_State::empty);
}

/****** Coordonate managment functions ******/

std::string get_case_written_coordonates(Pos coordonates)
{
    return coordonates_letter[coordonates.y] + std::to_string(coordonates.x + 1);
}
int pos_to_line(Pos pos)
{
    return pos.x + (pos.y * 8);
}
Pos line_to_pos(int l)
{
    return {l % 8, l / 8};
}