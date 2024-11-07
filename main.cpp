#include "my_lab.h"

struct Point {
    int x, y, z;

    bool operator<(const Point& other) const {
        return (x < other.x) || (x == other.x && y < other.y) || (x == other.x && y == other.y && z < other.z);
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
        return os;
    }
};

int main() {
    Set<int> intSet;
    intSet.insert(1);
    intSet.insert(2);
    intSet.insert(3);
    intSet.insert(2);
    cout << "Int Set: " << intSet << endl;

    Set<Point> pointSet;
    pointSet.insert({1, 2, 3});
    pointSet.insert({4, 5, 6});
    pointSet.insert({1, 2, 3}); // Проверка на уникальность
    cout << "Point Set: " << pointSet << endl;

    Set<int> anotherSet;
    anotherSet.insert(2);
    anotherSet.insert(5);
    try {
        Set<int> unionSet = intSet.unionWith(anotherSet);
        cout << "Union of Sets: " << unionSet << endl;
    } catch (const std::exception& e) {
        cout << "Exception do: " << e.what() << endl;
    }

    return 0;
}
