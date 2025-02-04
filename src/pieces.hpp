#include <cstddef>
#include <string>
#include <utility>
#include <vector>

#ifndef PIECES_ATTRIBUTES
const std::vector<int>         piece_value_by_type{9, 5, 3, 3, 1, 0};
const std::vector<int>         piece_n_move_directions_by_type{8, 4, 4, 8, 3, 8};
const std::vector<bool>        piece_inf_range_by_type{true, true, true, false, false, false};
const std::vector<std::string> piece_written_name_by_type{"Queen", "Tower", "Bishop", "Knight", "Pawn", "King"};

// Direction operators used to create the mouvement operators
// int front(int x)
// {
//     return x++;
// };
// int back(int x)
// {
//     return x--;
// };
// int left(int y)
// {
//     return y++;
// };
// int right(int y)
// {
//     return y--;
// };
// int still(int a)
// {
//     return a--;
// }

// // Direction operators used to calculate the different move possibilities of the piece
// std::pair<int, int> straight_move(int x, int y, int (*v_direction)(int), int (*h_direction)(int))
// {
//     return std::make_pair(v_direction(x), h_direction(y));
// };
// std::pair<int, int> L_move(int a, int b, int (*main_direction)(int), int (*second_direction)(int))
// {
//     return std::make_pair(main_direction(main_direction(a)), second_direction(b));
// };

const std::vector<std::vector<std::pair<int, int> (*)(int, int)>> piece_move_set_by_type{
    {
        [](int x, int y) { return std::make_pair(x++, y); },
        [](int x, int y) { return std::make_pair(x--, y); },
        [](int x, int y) { return std::make_pair(x, y++); },
        [](int x, int y) { return std::make_pair(x, y--); },
        [](int x, int y) { return std::make_pair(x++, y++); },
        [](int x, int y) { return std::make_pair(x--, y++); },
        [](int x, int y) { return std::make_pair(x--, y--); },
        [](int x, int y) { return std::make_pair(x++, y--); },
    },
    {
        [](int x, int y) { return std::make_pair(x++, y); },
        [](int x, int y) { return std::make_pair(x--, y); },
        [](int x, int y) { return std::make_pair(x, y++); },
        [](int x, int y) { return std::make_pair(x, y--); },
    },
    {
        [](int x, int y) { return std::make_pair(x++, y++); },
        [](int x, int y) { return std::make_pair(x--, y++); },
        [](int x, int y) { return std::make_pair(x--, y--); },
        [](int x, int y) { return std::make_pair(x++, y--); },
    },
    {
        [](int x, int y) { return std::make_pair(x += 2, y++); },
        [](int x, int y) { return std::make_pair(x++, y += 2); },
        [](int x, int y) { return std::make_pair(x += 2, y--); },
        [](int x, int y) { return std::make_pair(x--, y += 2); },
        [](int x, int y) { return std::make_pair(x -= 2, y++); },
        [](int x, int y) { return std::make_pair(x++, y -= 2); },
        [](int x, int y) { return std::make_pair(x -= 2, y--); },
        [](int x, int y) { return std::make_pair(x--, y -= 2); },
    },
    {
        [](int x, int y) { return std::make_pair(x++, y); },
        [](int x, int y) { return std::make_pair(x++, y++); },
        [](int x, int y) { return std::make_pair(x++, y--); },
    },
    {
        [](int x, int y) { return std::make_pair(x++, y); },
        [](int x, int y) { return std::make_pair(x--, y); },
        [](int x, int y) { return std::make_pair(x, y++); },
        [](int x, int y) { return std::make_pair(x, y--); },
        [](int x, int y) { return std::make_pair(x++, y++); },
        [](int x, int y) { return std::make_pair(x--, y++); },
        [](int x, int y) { return std::make_pair(x--, y--); },
        [](int x, int y) { return std::make_pair(x++, y--); },
    },
};

const std::vector<int> pieces_alignement{1, 3, 2, 0, 5, 2, 3, 1};

#endif

enum class Piece_type : int {
    Queen,
    Tower,
    Bishop,
    Knight,
    Pawn,
    King
};

enum class Color : int {
    black,
    white
};

class Piece {
private:
    int pos_x{};
    int pos_y{};

    int value;

    bool as_moved{false};

public:
    Piece_type type{};
    Color      color{};

    Piece(Piece_type piece_type, Color color, int pos_x, int pos_y);

    // The piece move
    void move(int pos_x, int pos_y);
    // The piece is taken and removed from the board
    void remove();
    // Take another piece, return the value of the taken piece
    int take(Piece taken_piece);

    std::pair<int, int> get_coordonates();

    // Get the possible moves of the piece
    std::vector<std::pair<int, int>> get_moves();
};