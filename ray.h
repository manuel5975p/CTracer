#ifndef RAY_H
#define RAY_H
#include "vec3.h"
#include <iostream>
#include <cmath>
#include <stack>
struct ray{
	std::stack<vec3> colorStack;
	vec3 o;
	vec3 l;
	ray(const vec3& d,vec3 s) : l(s.normalized()), o(d){}
	ray() : l(), o(){}
	ray(const ray& k) : o(k.o), l(k.l){
		l.normalize();
	}
	
	friend std::ostream& operator<<(std::ostream& out,const ray& o){
		out << o.o << " + t * " << o.l;
		return out;
	}
	ray& operator=(ray&& other){
		o = other.o;
		l = other.l;
		colorStack = std::move(other.colorStack);
		return *this;
	}
};
#endif