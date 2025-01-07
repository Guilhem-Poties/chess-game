#include <pair>
#include <vector>

enum class Piece_type : int {
    Queen,
    Tower,
    Bishop,
    Knight,
    Pawn,
    King
};

enum class Color : bool {
    black,
    white
};

struct Piece {
    Piece_type type;
    Color      color;

    int pos_x;
    int pos_y;

    bool as_moved;

    int point;

    void move();
    int  remove();
    void take(Piece taken_piece);

    std::vector<std::pair<int, int>> get_moves();
};