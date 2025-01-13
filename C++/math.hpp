#include <iostream>
#include <cmath>
#include <random>

namespace Math
{
    long double randomReal(long double min=0,long double max=1) {
        static std::random_device rseed;
        static std::mt19937 rng(rseed());
        std::uniform_real_distribution<long double> dist(min,max);
        return dist(rng);
    }
    
    long int randomInt(long int min=0,long int max=1) {
        static std::random_device rseed;
        static std::mt19937 rng(rseed());
        std::uniform_int_distribution<long int> dist(min,max);
        return dist(rng);
    }

    struct Vector2{
        double x;
        double y;
        Vector2() : x(0),y(0) {}
        Vector2(double x,double y) : x(x),y(y) {}
        Vector2 operator+(const Vector2& other) {
            return { this->x + other.x , this->y + other.y };
        }
        Vector2 operator-(const Vector2& other) {
            return { this->x - other.x , this->y - other.y };
        }
        Vector2& operator=(const Vector2& other) {
            if(this != &other) 
            {
                this->x = x;
                this->y = y;
            }
            return *this;
        }
        bool operator==(const Vector2& other) {
            return (this->x == other.x && this->y == other.y);
        }
        bool operator!=(const Vector2& other) {
            return !(this->x == other.x && this->y == other.y);
            
        }
        friend std::ostream& operator<<(std::ostream& os, const Vector2& other) {
            os << "("<<other.x<<","<<other.y<<")";  
            return os;
        }
        double magnitude() 
        {
            return sqrt(this->x*this->x + this->y*this->y);
        }
        double norm() {
            return this->x*this->x + this->y*this->y;
        }
    };
    struct Vector3{
        double x;
        double y;
        double z;
        Vector3() : x(0),y(0),z(0) {}
        Vector3(double x,double y,double z) : x(x),y(y),z(0) {}
        Vector3 operator+(const Vector3& other) 
        {
            return { this->x + other.x , this->y + other.y,this->z + other.z };
        }
        Vector3 operator-(const Vector3& other) 
        {
            return { this->x - other.x , this->y - other.y,this->z - other.y };
        }
        Vector3& operator=(const Vector3& other) 
        {
            if(this != &other) {
                this->x = other.x;
                this->y = other.y;
                this->z = other.z;
            }
        }
        
        bool operator==(const Vector3& other) 
        {
            return (this->x == other.x && this->y == other.y && this->z == other.z);
        }
        bool operator!=(const Vector3& other) 
        {
            return !(this->x == other.x && this->y == other.y && this->z == other.z);
        }
        friend std::ostream& operator<<(std::ostream& os, const Vector3& other) 
        {
            os << "("<<other.x<<","<<other.y<<","<<other.z<<")";  
            return os;
        }
        double magnitude() 
        {
            return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
        }
        double norm() 
        {
            return this->x*this->x + this->y*this->y + this->z *this->z;
        }
    };
} // namespace Math


