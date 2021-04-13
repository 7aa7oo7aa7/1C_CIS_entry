#include "cpp_parser.cpp"

struct Point {
    using IntCoordinate = int64_t;
    using FloatCoordinate = long double;
    explicit Point(IntCoordinate x, IntCoordinate y) : x(x), y(y), segment(0), is_left(false) {}
    IntCoordinate x;
    IntCoordinate y;
    int segment;  // number of segment which end it is
    bool is_left;  // true if left in segment, false if right
};

std::istream& operator>>(std::istream& in, Point& point) {
    in >> point.x >> point.y;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
    out << point.x << ' ' << point.y;
    return out;
}

bool operator<(const Point& left, const Point& right) {
    return ((std::tie(left.x, left.y) < std::tie(right.x, right.y))
    || ((std::tie(left.x, left.y) == std::tie(right.x, right.y)) && left.is_left));
}

struct Segment {
    explicit Segment(const Point& first, const Point& second) :
        left_point(std::min(first, second)), right_point(std::max(first, second)) {}
    Point left_point;
    Point right_point;
    Point::FloatCoordinate GetYCoordinate(Point::FloatCoordinate x) const;
};

Point::FloatCoordinate Segment::GetYCoordinate(Point::FloatCoordinate x) const {
    assert(left_point.x <= x + 0.0001 && x - 0.0001 <= right_point.x);  // check if x is within segment
    // we can get more precise values if x is segment end coordinate
    if (x == left_point.x) {
        return left_point.y;
    } else if (x == right_point.x) {
        return right_point.y;
    }
    // count K from (x,y) = (x1,y1) + K * ((x2,y2) - (x1,y1)), then get y value for such K
    Point::FloatCoordinate coefficient = static_cast<Point::FloatCoordinate>(right_point.y - left_point.y)
        / static_cast<Point::FloatCoordinate>(right_point.x - left_point.x);
    return (left_point.y + coefficient * (x - left_point.x));
}

bool operator<(const Segment& left, const Segment& right) {
    Point::IntCoordinate x = std::max(left.left_point.x, right.left_point.x);
    return (left.GetYCoordinate(x) < right.GetYCoordinate(x) - 0.0001);
}

std::multiset<Point> get_vertices(std::vector<std::vector<int>> png_data) {

}

std::vector<Segment> get_edges(const std::vector<std::vector<int>>& png_data) {

}
