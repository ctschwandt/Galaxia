/*****************************************************************************
File : vec2.h
Author: C. Schwandt
Date : 04/04/2024

Description
This is the header file of the vec2 class.

Each vec2 object models a 2-dimensional vector with double coordinates. The
methods and operators supported are described below. In the following, u, v,
and w are vec2 objects while c, d are doubles.

vec2 u(x,y)    - Constructor. This sets the x and y values of u to values of
                  parameters x and y respectively. The default values are 0,0
                  respectively.

std::cout << u  - Prints vector u. The format is "<x, y>" where x and y
                  are the x and y values of u.

std::cin >> u   - Input for u.

u.get_x()       - Returns the x_ value of vec2d object u.
u.get_y()       - Returns the y_ value of vec2d object u.
u.set_x(x0)     - Sets the x_ value of u to the value of x0.
u.set_y(y0)     - Sets the y_ value of u to the value of y0
u[i]            - Returns the x_ value or a reference to the x_ value of u
                  if i is 0; otherwise the y_ value or reference to the y_
                  value is returned.

u == v          - Returns true iff the respective x_,y_ values of u and v are
the same.
u != v          - The boolean opposite of (u == v)
u = v           - Copies the x,y values of v to u.

+u              - Returns a copy of u.
u += v          - Increments the x_ and y_ values of u by the x and y values
                  of v respectively. A reference to u is returned so that
                  you can also execute
                  (u += v) += w.
u + v           - Returns the vector sum of u and v.
-u              - Return the negative of u, i.e., the vec2d object returned
                  has x_,y_ values which are the negative of the x_,y_ values of
                  u.
u -= v          - Decrements the x_ and y_ values of u by the x_ and y_ values
                  of v. A reference to u is returned so that
                  you can also execute
                  (u -= v) -= w.
u - v           - Returns the vector difference of u and v.

u *= c          - Multiplies the x_,y_ values of u by double c and set the
                  x_,y_ values to these new values (respectively). A
                 reference to u is returned so that you can also execute
                 (u *= c) *= d.
u * c           - Returns the vector scalar product of vector u by double
                  c, i.e., a vec2d object is returned where the x_,y_ values
                  of this new vec2d object are the x_,y_ values of u
                  multiplied by c.
c * u           - Similar to u * c.

u /= c          - Divides the x,y values of u by double c and set the x_,y_ 
                  values to these new values (respectively). A reference
                  to u is returned so that you can also execute
                  (u /= c) /= d.
u / c           - Returns the vector scalar product of vector u by the double
                  (1/c).

len(u)          - Returns the length of vector u as a double. This is the
                  square root of x_*x_ + y_*y_ where x_,y_ are the values
                  in u. Note that this is a non-member function.
u.len()         - Same as len(u) except that this is a method.

dotprod(u, v)   - Returns the dot product of vectors u and v as a double.
norm(u)         - Return the normalized vector of u, i.e., this function
                  returns u / len(u), a vector of length 1 going in the
                  same direction as u.

******************************************************************************/
#ifndef VEC2_H
#define VEC2_H

#include <iostream>
#include <cmath>


class ValueError {};

template < typename T >
class vec2
{
public:
    vec2(T x = 0, T y = 0)
        : x_(x), y_(y)
    {}
    
    bool operator==(const vec2 &) const;
    bool operator!=(const vec2 &) const;
    
    T get_x() const { return x_; }
    T & get_x() { return x_ ;}
    T get_y() const { return y_; }
    T & get_y() { return y_; }
    
    void set_x(T x) { x_ = x; }
    void set_y(T y) { y_ = y; }
    
    T operator[](int) const;
    T & operator[](int);
    
    vec2 operator+() const;
    vec2 & operator+=(const vec2 &);
    vec2 operator+(const vec2 &) const;
    
    vec2 operator-() const;
    vec2 & operator-=(const vec2 &);
    vec2 operator-(const vec2 &) const;
    
    vec2 & operator*=(T);
    vec2 operator*(T) const;
    
    vec2 & operator/=(T);    
    vec2 operator/(T) const;
    
    double len() const;
private:
    T x_, y_;  
};

//=======================================
// Methods
//=======================================

template < typename T >
bool vec2< T >::operator==(const vec2 & v) const
{
    return (get_x() == v.get_x() && get_y() == v.get_y());
}

template < typename T >
bool vec2< T >::operator!=(const vec2 & v) const
{
    return !((*this) == v);
}

template < typename T >
T vec2< T >::operator[](int i) const
{
    if (i != 0 && i != 1)
    {
        throw ValueError();
    }

    if (i == 0)
        return x_;
    else
        return y_;
}

template < typename T >
T & vec2< T >::operator[](int i)
{
    if (i != 0 && i != 1)
    {
        throw ValueError();
    }

    if (i == 0)
        return x_;
    else
        return y_;
}

template < typename T >
vec2< T > vec2< T >::operator+() const
{
    return (*this);
}

template < typename T >
vec2< T > & vec2< T >::operator+=(const vec2 & v)
{
    set_x((*this)[0] + v[0]);
    set_y((*this)[1] + v[1]);
    return (*this);
}

template < typename T >
vec2< T > vec2< T >::operator+(const vec2 & v) const
{
    return (vec2(*this) += v);
}

template < typename T >
vec2< T > vec2< T >::operator-() const
{
    return (vec2(-(*this)[0], -(*this)[1]));
}

template < typename T >
vec2< T > & vec2< T >::operator-=(const vec2 & v)
{
    return ((*this) += -v);
}

template < typename T >
vec2< T > vec2< T >::operator-(const vec2 & v) const
{
    return (vec2(*this) += -v);
}

template < typename T >
vec2< T > & vec2< T >::operator*=(T c)
{
    set_x((*this)[0] * c);
    set_y((*this)[1] * c);
    return (*this);
}

template < typename T >
vec2< T > vec2< T >::operator*(T c) const
{
    return vec2(*this) *= c;
}

template < typename T >
vec2< T > & vec2< T >::operator/=(T c)
{
    set_x((*this)[0] / c);
    set_y((*this)[1] / c);
    return (*this);
}

template < typename T >
vec2< T > vec2< T >::operator/(T c) const
{
    return vec2(*this) /= c;
}

template < typename T > // can this be made without a template?
double vec2< T >::len() const
{
    return sqrt((*this)[0] * (*this)[0]
                + (*this)[1] * (*this)[1]);
}

//=======================================
// Functions
//=======================================

template < typename T >
vec2< T > operator*(T c, const vec2< T > & v)
{
    return v * c;
}

template < typename T >
double len(const vec2< T > & v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1]);
}

template < typename T >
T dotprod(const vec2< T > & u, const vec2< T > & v)
{
    return u[0] * v[0] + u[1] * v[1];
}

template < typename T >
vec2< T > norm(const vec2< T > & v)
{
    return v / v.len();
}

// Prints the vec2 'v' in the following format: If 'v' is vec2d(1.1, 2.2),
// then The output is <1.1, 2.2>.
template < typename T >
std::ostream & operator<<(std::ostream & cout, const vec2< T > & v)
{
    cout << '<' << v.get_x() << ", " << v.get_y() << "> ";
    return cout;
}

template < typename T >
std::istream & operator>>(std::istream & cin, vec2< T > & v)
{
    cin >> v.get_x();
    cin >> v.get_y();
    return cin;
}


//========================================
// Typedefs
//========================================

typedef vec2< int > vec2i;
typedef vec2< float > vec2f;
typedef vec2< double > vec2d;

#endif
