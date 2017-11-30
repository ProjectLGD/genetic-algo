#include "../include/Vec3.h"

Vec3::Vec3() {
}

Vec3::Vec3(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;
}


Vec3::~Vec3() {
    // cout << "Deconstructing Vec3" << endl;
}

float Vec3::get_distance(Vec3 target) {
    return sqrt(pow(target.x - this->x, 2) + pow(target.y - this->y, 2) + pow(target.z - this->z, 2));
}

ostream& operator<< (ostream & out, const Vec3 &data) {
    out << "X Y Z: " << data.x << " " << data.y << " " << data.z;
    return out;
}

Vec3 operator+(const Vec3 &t, const Vec3 &o) {
    return Vec3(t.x + o.x, t.y + o.y, t.z + o.z);
}

Vec3 operator-(const Vec3 &t, const Vec3 &o) {
    return Vec3(t.x - o.x, t.y - o.y, t.z - o.z);
}

bool operator<(const Vec3 &l, const Vec3 &r) {
    return (l.x < r.x) && (l.y < r.y) && (l.z < r.z);
}

bool operator>(const Vec3 &l, const Vec3 &r) {
    return r < l;
}

bool operator<=(const Vec3 &l, const Vec3 &r) {
    return !(l > r);
}

bool operator>=(const Vec3 &l, const Vec3 &r) {
    return !(l < r);
}

bool operator==(const Vec3 &l, const Vec3 &r) {
    return (l.x == r.x) && (l.y == r.y) && (l.z == r.z);
}

bool operator!=(const Vec3 &l, const Vec3 &r) {
    return !(l == r);
}
