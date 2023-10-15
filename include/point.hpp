#ifndef __LAB_POINT_HPP__
#define __LAB_POINT_HPP__

#include <ostream>
#include "utility.hpp"

template<class T>
class Point
{
public:
  T x;
  T y;
  Point(T x = T(), T y = T()) { this->x = x; this->y = y; }
  Point operator+(const Point& p) const { return Point(this->x + p.x, this->y + p.y); }
  Point operator-(const Point& p) const { return Point(this->x - p.x, this->y - p.y); }
  //bool operator==(const Point& p) const { return this->x == p.x && this->y == p.y; }
  bool operator==(const Point& p) const { return is_zero<T>(this->x - p.x) && is_zero<T>(this->y - p.y); }
  bool operator!=(const Point& p) const { return !this->operator==(p); }
  T abs_sq(void) const { return this->x*this->x + this->y*this->y; }
  bool operator<=(const Point& p) const { return points_le<T>(*this, p); }
  bool operator>(const Point& p) const { return !points_le<T>(*this, p); }
  bool operator<(const Point& p) const { return !points_le<T>(p, *this); }
  bool operator>=(const Point& p) const { return points_le<T>(p, *this); }
};

template<class T>
std::ostream& operator<<(std::ostream& out, const Point<T>& p)
{
  out << '(' << p.x << ',' << ' ' << p.y << ')';
  return out;
}

typedef Point<int> Pointi;
typedef Point<float> Pointf;
typedef Point<double> Pointd;

#endif
