#ifndef OBJECTS_H
#define OBJECTS_H
#include "vec3.h"
#include "ray.h"
#include <cassert>
#include <cmath>
struct sphere{
	vec3 loc;
	vec3 color;
	v_t rad;
	sphere(const vec3& location,v_t radius) : loc(location), rad(radius){
		
	}
	sphere(v_t radius,const vec3& location) : rad(radius), loc(location){
		
	}
	sphere& setColor(const vec3& c){
		color = c;
		return *this;
	}
	sphere& setColor(v_t r,v_t g,v_t b){
		return setColor(vec3(r,g,b));
	}
	vec3 intersectionPoint(const ray& ra){
		assert(std::abs(ra.l.norm() - 1) <= 0.0000001);
		v_t h1 = (ra.l * (ra.o - loc));
		v_t disc = h1 * h1 - ((ra.o - loc).normsq()) + rad * rad;
		if(disc < 0){
			return vec3();
		}
		v_t d = -(h1 + disc);
		if(d <= 0.00001)
		return vec3();
		return ra.o + (ra.l * d);
	}
	vec3 operator>>(const ray& r){
		return intersectionPoint(r);
	}
	
	ray reflectingRay(ray& inc){
		vec3 ip = intersectionPoint(inc, verbose);
		assert(!(ip.x == 0 && ip.y == 0 && ip.z == 0));
		vec3 planevec = !(loc - ip);
		vec3 adder = (planevec) * (planevec * inc.l);
		adder *= -2.0;
		ray ret = ray(ip,inc.l + adder);
		ret.colorStack = inc.colorStack;
		ret.colorStack.push(color);
		return ret;
	}
};
struct light_sphere{
	vec3 loc;
	vec3 color;
	v_t rad;
	v_t brightness;
	light_sphere& setColor(const vec3& c){
		color = c;
		return *this;
	}
	light_sphere& setColor(v_t r,v_t g,v_t b){
		return setColor(vec3(r,g,b));
	}
	light_sphere(const vec3& location,v_t radius) : loc(location), rad(radius),brightness(1){
		
	}
	light_sphere(v_t radius,const vec3& location) : rad(radius), loc(location),brightness(1){
		
	}
	vec3 intersectionPoint(const ray& ra){
		v_t h1 = (ra.l * (ra.o - loc));
		v_t disc = h1 * h1 - (ra.o - loc).normsq() + rad * rad;
		if(disc < 0){
			return vec3();
		}
		disc = std::sqrt(disc);
		v_t d = -(h1 + disc);
		if(d <= 0.000001)
		return vec3();
		return ra.o + (ra.l * d);
	}
	vec3 operator>>(const ray& r){
		return intersectionPoint(r);
	}
	ray reflectingRay(ray& inc){
		vec3 ip = (*this) >> inc;
		vec3 r = (ip - loc).normalized();
		ray ret = ray(ip,inc.l + ((inc.l * r) * 2));
		ret.colorStack = inc.colorStack;
		ret.colorStack.push(color);
		return ret;
	}
};
#endif