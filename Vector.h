#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <cmath>
#include <iostream>

class Vector2 {
  public:

    Vector2() : m_x{0.f}, m_y{0.f} {}

    friend std::istream& operator>>(std::istream& _is, Vector2& _v) {
      return _is >> _v.m_x >> _v.m_y;
    }

    friend std::ostream& operator<<(std::ostream& _os, const Vector2& _v) {
      return _os << _v.m_x << " " << _v.m_y;
    }

  private:
    float m_x, m_y;
};

class Vector3 {
  private:
    float x, y, z;

  public:
    Vector3() : x{0.f}, y{0.f}, z{0.f} {}

    //Constructor called when new Vector3 is initiated
    Vector3(float _x, float _y, float _z): x{_x}, y{_y}, z{_z} {
    }

    //Returns x value
    float getX() const { return x; }
    //Returns y value
    float getY() const { return y; }
    //Returns z value
    float getZ() const { return z; }

    //Operator +
    //Ex) Vector1 = Vector2 + Vector3
    Vector3 operator+(const Vector3& _other) const {
      return Vector3(x + _other.x, y + _other.y, z + _other.z);
    }

    //Operator -
    //Ex) Vector1 = Vector2 - Vector3
    Vector3 operator-(const Vector3& _other) const {
      return Vector3(x - _other.x, y - _other.y, z -_other.z);
    }

    //Operator +=
    //Ex) Vector1 += Vector2
    Vector3& operator+=(const Vector3& _other) {
      x += _other.x;
      y += _other.y;
      z += _other.z;
      return *this;
    }

    //Operator -=
    //Ex) Vector1 -= Vector2
    Vector3& operator-=(const Vector3& _other) {
      x -= _other.x;
      y -= _other.y;
      z -= _other.z;
      return *this;
    }

    //Operator ==
    //Ex) if(Vector1 == Vector2)
    bool operator==(const Vector3& _other) const {
      return x == _other.x && y == _other.y && z == _other.z;
    }

    //Operator !=
    //Ex) if(Vector1 != Vector2)
    bool operator!=(const Vector3& _other) const {
      return !(*this == _other);
    }

    //Operator *
    Vector3 operator*(float f) const {
      return Vector3(x*f, y*f, z*f);
    }
    Vector3 operator/(float f) const {
      return Vector3(x/f, y/f, z/f);
    }
    Vector3& operator*=(float f) {
      x *= f;
      y *= f;
      z *= f;
      return *this;
    }
    Vector3& operator/=(float f) {
      x /= f;
      y /= f;
      z /= f;
      return *this;
    }
    //Multiplies by another vector
    float operator*(const Vector3& b) const {
        return x * b.x + y * b.y + z * b.z;
    }

    //Returns vector squared
    float normsqr() const {
      return operator*(*this);
    }

    //Returns Sqrt of vector squared
    //Calculates the distance from origin
    float norm() const {
        return sqrt(normsqr());
    }

    Vector3 normalized() const {
      float l = norm();
      return operator/(l);
    }

    Vector3& normalize() {
      float l = norm();
      return operator/=(l);
    }

    Vector3 proj(const Vector3& b) const {
      Vector3 hat = b.normalized();
      return hat * (hat * (*this));
    }

    Vector3 orth(const Vector3& b) const {
      return (*this) - proj(b);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
      return os << v.x << " " << v.y << " " << v.z;
    }

    friend std::istream& operator>>(std::istream& is, Vector3& v) {
      return is >> v.x >> v.y >> v.z;
    }
};

#endif
