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

class Vector2{
    private:
        float x, y;
    public:
        Vector2(float _x, float _y): x{_x}, y{_y} {}
        Vector2 operator+(Vector2 _other){
            return Vector2(x + _other.x, y + _other.y);
        }
        Vector2 operator-(Vector2 _other){
            return Vector2(x - _other.x, y - _other.y);
        }
        float getX(){
            return x;
        }
        float getY(){
            return y;
        }
        
};
class Vector3{
    private:
        float x, y, z;
    public:
        Vector3(float _x,float _y,float _z): x{_x}, y{_y}, z{_z}{}
        Vector3 operator+(Vector3 _other){
            return Vector3(x + _other.x, y + _other.y, z + _other.z);
        }
        Vector3 operator-(Vector3 _other){
            return Vector3(x - _other.x, y - _other.y, z -_other.z);
        }
        Vector3 operator +=(Vector3 _other){
           x += _other.x;
           y += _other.y;
           z += _other.z;
        }
        Vector3 operator -=(Vector3 _other){
            x -= _other.x;
            y -= _other.y;
            z -= _other.z;
        }
        
};
int main(int argc, char argv) {    
    //PointOne
    cout<<"Enter Point One X:";
    float x; 
    cin >> x;
    cout<<"Enter Point One Y:";
    float y;
    cin >> y;
    cout<<"\n";
    Vector2 PointOne = Vector2(x, y);
    
    //PointTwo
    cout<<"Enter Point Two X:";
    cin >> x;
    cout<<"Enter Point Two Y:";
    cin >> y;
    cout<<"\n";
    Vector2 PointTwo = Vector2(x, y);
    
     //Add Subtract or none
    cout<<"\n Type A to Add vectors S to Subtract and N for No action: ";
    char input;
    cin >> input;
    if((input == 'n')||(input == 'N')){
    }else if((input == 'a')||(input == 'A')){
        PointTwo = PointOne + PointTwo;
    }else if((input == 's')||(input == 'S')){
        PointTwo = PointOne - PointTwo;
    }
    //Finds distance from origin PointOne
    float ChangeX = PointOne.getX();
    float ChangeY = PointOne.getY();
    if(ChangeX < 0){
        ChangeX *= -1;
    }
    if(ChangeY < 0){
        ChangeY *= -1;
    }
    float DistanceOne = pow((ChangeY * ChangeY) + (ChangeX * ChangeX),0.5);
    cout<<"Vector Statistics: \n";
    cout<< "Vector 1 Distance from origin: " << DistanceOne <<"\n";
   
     //Finds distance from origin PointTwo
    ChangeX = PointTwo.getX();
    ChangeY = PointOne.getY();
    if(ChangeX < 0){
        ChangeX *= -1;
    }
    if(ChangeY < 0){
        ChangeY *= -1;
    }
    float DistanceTwo = pow((ChangeY * ChangeY) + (ChangeX * ChangeX),0.5);
    cout<< "Vector 2 Distance from origin: " << DistanceTwo <<"\n";
    
   
    //Make graph
    for(float r = 10; r > -11; r--){
        for(int c = -10; c < 11; c+= 1){
            if((r == PointOne.getY())&&(c == PointOne.getX())){
                cout<<" 1 ";
            }else if((r == PointTwo.getY())&&(c == PointTwo.getX())){
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
}

/*
 
 
 */