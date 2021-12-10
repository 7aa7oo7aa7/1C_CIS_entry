#include <iostream>
#include <cassert>
#include <set>
#include <cstdint>
#include <tuple>
#include <vector>
#include <optional>
#include "converter.cpp"

Point::IntCoordinate GetOrientedArea(const Point& first, const Point& second, const Point& third) {
    // count double value of oriented triangle area (as a determinant)
    return ((second.x - first.x) * (third.y - first.y) - (second.y - first.y) * (third.x - first.x));
}

bool DoIntersectProjections(Segment first, Segment second) {
    // check x projections, points are already sorted
    if (std::max(first.left_point.x, second.left_point.x) > std::min(first.right_point.x, second.right_point.x)) {
        return false;
    }
    // sort segment ends for y comparison
    if (first.left_point.y > first.right_point.y) {
        std::swap(first.left_point, first.right_point);
    }
    if (second.left_point.y > second.right_point.y) {
        std::swap(second.left_point, second.right_point);
    }
    // check y projections
    return (std::max(first.left_point.y, second.left_point.y) <= std::min(first.right_point.y, second.right_point.y));
}

bool DoIntersect(const Segment& first, const Segment& second) {
    // segments intersect <=> their projections intersect
    // && ends of segment 1/2 lie in different half-planes of segment 2/1
    if (!DoIntersectProjections(first, second)) {
        return false;
    }
    Point::IntCoordinate oriented_area_1 =
        GetOrientedArea(first.left_point, first.right_point, second.left_point);
    Point::IntCoordinate oriented_area_2 =
        GetOrientedArea(first.left_point, first.right_point, second.right_point);
    int area_1_sign = (oriented_area_1 > 0 ? 1 : (oriented_area_1 < 0 ? -1 : 0));
    int area_2_sign = (oriented_area_2 > 0 ? 1 : (oriented_area_2 < 0 ? -1 : 0));
    if (area_1_sign * area_2_sign > 0) {
        return false;
    }
    oriented_area_1 = GetOrientedArea(second.left_point, second.right_point, first.left_point);
    oriented_area_2 = GetOrientedArea(second.left_point, second.right_point, first.right_point);
    area_1_sign = (oriented_area_1 > 0 ? 1 : (oriented_area_1 < 0 ? -1 : 0));
    area_2_sign = (oriented_area_2 > 0 ? 1 : (oriented_area_2 < 0 ? -1 : 0));
    return (area_1_sign * area_2_sign <= 0);
}

int FindSegmentsIntersections(const std::multiset<Point>& points,
                            const std::vector<Segment>& segments) {  // scan line algorithm

    int intersection_num = 0;
    std::multiset<Segment> current_segments;
    std::vector<std::multiset<Segment>::iterator> segments_iterators(segments.size());  // segment iterators in current_segments

    // iterate from left to right
    for (const auto& i : points) {
        if (i.is_left) {

            // add new segment
            auto current_iter = current_segments.emplace(segments[i.segment]);
            segments_iterators[i.segment] = current_iter;

            if (current_iter != current_segments.begin()
                && DoIntersect(*current_iter, *(std::prev(current_iter)))) {

                ++intersection_num;

            } else if (std::next(current_iter) != current_segments.end()
                && DoIntersect(*current_iter, *(std::next(current_iter)))) {

                ++intersection_num;

            }

        } else {

            // remove a segment
            auto current_iter = current_segments.erase(segments_iterators[i.segment]);

            if (current_iter != current_segments.end() && current_iter != current_segments.begin()
                && DoIntersect(*current_iter, *(std::prev(current_iter)))) {

                ++intersection_num;

            }

        }
    }

    return intersection_num - get_vertex_num();

}

int main() {

    std::multiset<Point> points = get_vertices(read_data());
    std::vector<Segment> segments = get_edges(read_data());

    std::cout << FindSegmentsIntersections(points, segments) << std::endl;

    return 0;

}
