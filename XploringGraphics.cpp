/*
 * File:   main.cpp
 * Author: Maxwell
 *
 * Created on September 15, 2018, 11:16 PM
 */

#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

class Vector3{
  private:
    float x, y, z;
    Vector3 hat ();

  public:
    Vector3() : x{0.f}, y{0.f} {}
    //Constructor called when new Vector3 is initiated
    Vector3(float _x,float _y,float _z): x{_x}, y{_y}, z{_z} {
    }

    //Operator +
    //Ex) Vector1 = Vector2 + Vector3
    Vector3 operator+(Vector3 _other){
      return Vector3(x + _other.x, y + _other.y, z + _other.z);
    }

    //Operator -
    //Ex) Vector1 = Vector2 - Vector3
    Vector3 operator-(Vector3 _other){
      return Vector3(x - _other.x, y - _other.y, z -_other.z);
    }

    //Operator +=
    //Ex) Vector1 += Vector2
    Vector3 operator+=(Vector3 _other){
      x += _other.x;
      y += _other.y;
      z += _other.z;
    }

    //Operator -=
    //Ex) Vector1 -= Vector2
    Vector3 operator-=(Vector3 _other){
      x -= _other.x;
      y -= _other.y;
      z -= _other.z;
    }

    //Operator ==
    //Ex) if(Vector1 == Vector2)
    bool operator==(Vector3 _other) {
      return x == _other.x && y == _other.y && z == _other.z;
    }

    //Operator !=
    //Ex) if(Vector1 != Vector2)
    bool operator!=(Vector3 _other) {
      return !(*this == _other);
    }

    //Operator *
    Vector3 operator*(float f){
      return Vector3(x*f, y*f, z*f);
    }
    //Multiplies by another vector
    float operator*(Vector3 b){
        return x * b.x + y * b.y + z + b.z;
    }

    //Calculates the distance from origin
    float distance() {
      return sqrt(x*x + y*y + z*z);
    }

    //Returns x value
    float getX() { return x; }
    //Returns y value
    float getY() { return y; }
    //Returns z value
    float getZ() { return z; }
    
    //Returns vector squared
    float normsqr(){
        return x * x + y * y + z * z;
    }
    //Returns Sqrt of vector squared
    float norm(){
        return sqrt(x * x + y * y + z * z);
    }
    Vector3 normalized(){
        return Vector3(x / distance(), y / distance(), z / distance());
    }
    void nomalize(){
        float length = distance();
        x = x / length;
        y = y / length;
        z = z / length;
    }
    
    Vector3 proj(Vector3 b){
        float length = distance();
        b.hat() = Vector3(b.x / length, b.y / length, b.z / length);
        return Vector3(b.hat().x * x * b.hat().x, b.hat().y * y * b.hat().y, b.hat().z * z * b.hat().z);
    }
    
    friend ostream& operator<<(ostream& os, const Vector3& v) {
      return os << v.x << " " << v.y << " " << v.z;
    }

    friend istream& operator>>(istream& is, Vector3& v) {
      return is >> v.x >> v.y >> v.z;
    }
};

/*int main(int argc, char** argv) {
  //p1
  // To reduce implement operator>> and operator << for vectors
  cout<<"Enter Point One: ";
  Vector2 p1;
  cin >> p1;
  cout<<"\n";

  //p2
  cout<<"Enter Point Two: ";
  Vector2 p2;
  cin >> p2;
  cout<<"\n";

  // output points:
  cout << "Your points: " << p1 << ", " << p2 << endl;

  //Add Subtract or none
  cout<<"\n Type A to Add vectors S to Subtract and N for No action: ";
  char input;
  cin >> input;
  if((input == 'n')||(input == 'N')){
  }else if((input == 'a')||(input == 'A')){
    p2 = p1 + p2;
  }else if((input == 's')||(input == 'S')){
    p2 = p1 - p2;
  }

  //Finds distance from origin p1
  float ChangeX = p1.getX();
  float ChangeY = p1.getY();
  if(ChangeX < 0){
    ChangeX *= -1;
  }
  if(ChangeY < 0){
    ChangeY *= -1;
  }
  float DistanceOne = pow((ChangeY * ChangeY) + (ChangeX * ChangeX),0.5);
  cout<<"Vector Statistics: \n";
  cout<< "Vector 1 Distance from origin: " << DistanceOne <<"\n";

  //Finds distance from origin p2
  ChangeX = p2.getX();
  ChangeY = p1.getY();
  if(ChangeX < 0){
    ChangeX *= -1;
  }
  if(ChangeY < 0){
    ChangeY *= -1;
  }
  float DistanceTwo = pow((ChangeY * ChangeY) + (ChangeX * ChangeX),0.5);
  cout<< "Vector 2 Distance from origin: " << DistanceTwo <<"\n";


  //Make graph
  for(float r = 10; r > -11; r--){ // don't use float here
    for(int c = -10; c < 11; c+= 1){
      if((r == p1.getY())&&(c == p1.getX())){ // what if x and y
                                                          // aren't at an
                                                          // integer value
        cout<<" 1 ";
      }else if((r == p2.getY())&&(c == p2.getX())){ // Dito
        cout<< " 2 ";
      }else if(c == 0){
        cout<<" | ";
      }else if(r == 0){
        cout<<" - ";
      }else{
        cout<<" * ";
      }
    }
    cout<<"\n";
  }

  return 0;
} */