#include "board.hpp"

std::string get_case_written_coordonates(Pos coordonates)
{
    return coordonates_letter[coordonates.y] + std::to_string(coordonates.x + 1);
}

void Board::generate_board()
{
    for (size_t pos = 0; pos < 64; pos++)
    {
        this->_board.emplace_back(place_piece(pos));
    }
}

int pos_to_line(Pos pos)
{
    return pos.x + (pos.y * 8);
}
Pos line_to_pos(int l)
{
    return {l % 8, l / 8};
}

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

Piece* Board::take(Pos current_pos, Pos new_pos, bool en_passant)
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
bool Board::is_move_in_enemy_range(Pos move, Color color) const
{
    for (size_t i{0}; i < this->all_moves.size(); i++)
    {
        if (this->tile_state(line_to_pos(i), color) == Tile_State::enemy)
        {
            std::cout << "enemy " << i << "\n";
            if (std::find(this->all_moves.at(i).begin(), this->all_moves.at(i).end(), move) != this->all_moves.at(i).end())
                return true;
        }
    }
    return false;
}

bool Board::is_in_board(Pos pos) const
{
    return ((pos.x >= 0 && pos.x < 8) && (pos.y >= 0 && pos.y < 8));
}
Tile_State Board::tile_state(Pos pos, Color color) const
{
    return (this->at(pos) != nullptr ? ((this->at(pos)->get_color() == color) ? Tile_State::ally : Tile_State::enemy) : Tile_State::empty);
}