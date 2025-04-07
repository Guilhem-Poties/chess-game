#include <iostream>

// Structure for Positions with increase options
struct Pos {
    int x;
    int y;

    Pos incr_x(int incr) { return {this->x + incr, this->y}; };
    Pos incr_y(int incr) { return {this->x, this->y + incr}; };

    std::string to_string() { return std::to_string(x) + ", " + std::to_string(y) + "\n"; };
};

inline Pos operator+(Pos const& pos_a, Pos const& pos_b)
{
    return {pos_a.x + pos_b.x, pos_a.y + pos_b.y};
}
inline void operator+=(Pos& pos_a, Pos const& pos_b)
{
    pos_a = pos_a + pos_b;
}
inline Pos operator-(Pos const& pos_a, Pos const& pos_b)
{
    return {pos_a.x - pos_b.x, pos_a.y - pos_b.y};
}
inline Pos operator*(Pos const& pos, int mult)
{
    return {pos.x * 2, pos.y * 2};
}

inline bool operator==(Pos const& pos_a, Pos const& pos_b)
{
    return pos_a.x == pos_b.x && pos_a.y == pos_b.y;
}
inline bool operator!=(Pos const& pos_a, Pos const& pos_b)
{
    return !(pos_a == pos_b);
}