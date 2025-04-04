#include "board.hpp"
void Board::generate_board()
{
    for (int pos = 0; pos < 64; pos++)
    {
        this->_board.emplace_back(place_piece(pos));
    }
    this->all_moves.assign(64, {});
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
Piece* Board::move(Pos current_pos, Pos new_pos, bool en_passant, bool short_castle, bool long_castle)
{
    if (current_pos != new_pos)
    {
        this->move_history.push_back(std::make_pair(this->at(current_pos), std::make_pair(current_pos, new_pos)));

        Piece* captured_piece{this->at(new_pos)};

        if (en_passant)
        {
            captured_piece                                                                             = this->at(get_en_passant_pos(this->at(current_pos)->get_color(), new_pos));
            this->_board[pos_to_line(get_en_passant_pos(this->at(current_pos)->get_color(), new_pos))] = nullptr;
        }
        else if (short_castle)
            this->move(new_pos.incr_x(-1), new_pos.incr_x(1), false, false, false);
        else if (long_castle)
            this->move(new_pos.incr_x(2), new_pos.incr_x(-1), false, false, false);

        this->_board[pos_to_line(new_pos)]     = std::move(this->_board.at(pos_to_line(current_pos)));
        this->_board[pos_to_line(current_pos)] = nullptr;

        return captured_piece;
    }
    else
        return nullptr;
}
void Board::calculate_all_moves(bool deepsearch)
{
    this->all_moves = {};

    // this->all_moves = {};
    for (int i = 0; i < this->_board.size(); i++)
    {
        if (Piece* piece = this->at(line_to_pos(i)); piece != nullptr)
            all_moves.push_back(std::make_pair(line_to_pos(i), piece->get_possible_moves(*this, line_to_pos(i), deepsearch)));
        else
            all_moves.push_back({});
    }
}
bool Board::is_tower(Color piece_color, Pos piece_pos) const
{
    return this->tile_state(piece_pos, piece_color) == Tile_State::ally && dynamic_cast<Tower*>(this->at(piece_pos));
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
    return this->all_moves.at(pos_to_line(pos)).second;
}
bool Board::is_pos_in_piece_moveset(Pos pos_a, Pos pos_b) const
{
    return std::find(this->all_moves.at(pos_to_line(pos_a)).second.begin(), this->all_moves.at(pos_to_line(pos_a)).second.end(), pos_b) != this->all_moves.at(pos_to_line(pos_a)).second.end();
}

/****** Check managment functions ******/

bool Board::is_check(Color player)
{
    if (is_tile_attacked(this->king_pos(player), player))
    {
        return true;
    }
    else
        return false;
}
bool Board::is_checkmate(Color player)
{
    if (this->n_possible_moves(player) <= 0 && is_check(player))
        return true;
    else
        return false;
}
bool Board::is_stale_mate(Color player)
{
    if (this->n_possible_moves(player) <= 0 && !is_check(player))
        return true;
    else
        return false;
}
int Board::n_possible_moves(Color player) const
{
    std::vector<std::pair<Pos, std::vector<Pos>>> player_moves{};

    auto has_move{[player, this](const std::pair<Pos, std::vector<Pos>>& moves) {
        return this->tile_state(moves.first, player) == Tile_State::ally && moves.second.size() > 0;
    }}; // Check if the piece on the right color can move

    std::copy_if(this->all_moves.begin(), this->all_moves.end(), std::back_inserter(player_moves), has_move);
    return player_moves.size();
}
bool Board::is_king(Color piece_color, Pos piece_pos) const
{
    return this->tile_state(piece_pos, piece_color) == Tile_State::ally && dynamic_cast<King*>(this->at(piece_pos));
}
Pos Board::king_pos(Color king_color) const
{
    auto is_king = [king_color](const std::unique_ptr<Piece>& piece) {
        return piece != nullptr && piece.get()->get_color() == king_color && dynamic_cast<King*>(piece.get());
    };

    if (auto king_pos{std::find_if(this->_board.begin(), this->_board.end(), is_king)}; king_pos != this->_board.end())
        return line_to_pos(std::distance(this->_board.begin(), king_pos));
    else
        return {-1, -1};
}
bool Board::is_move_future_check(Pos piece_pos, Pos move) const
{
    Board future_board(*this);
    future_board._board = copy_board_vector(this->_board);

    bool en_passant{can_en_passant(future_board, get_en_passant_pos(future_board.at(piece_pos)->get_color(), move))};

    future_board.move(piece_pos, move, en_passant, false, false);
    future_board.calculate_all_moves(false);

    return future_board.is_check(this->at(piece_pos)->get_color());
}
bool Board::is_tile_attacked(Pos move, Color color) const
{
    for (std::pair<Pos, std::vector<Pos>> piece_moves : this->all_moves)
        if (this->tile_state(piece_moves.first, color) == Tile_State::enemy)
            if (std::find(piece_moves.second.begin(), piece_moves.second.end(), move) != piece_moves.second.end())
                return true;

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
std::vector<std::unique_ptr<Piece>> copy_board_vector(const std::vector<std::unique_ptr<Piece>>& original)
{
    std::vector<std::unique_ptr<Piece>> copy;
    for (const auto& elem : original)
    {
        if (elem != nullptr)
            copy.push_back(elem->clone()); // Crée un nouvel objet
        else
            copy.push_back(nullptr);
    }
    return copy;
}