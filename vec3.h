#ifndef VEC3_H
#define VEC3_H
#include <iostream>
using v_t = double;
struct vec3{
	v_t x,y,z;
	vec3();
	vec3(v_t a);
	vec3(v_t _x,v_t _y,v_t _z);
	vec3(const vec3& o);
	vec3(vec3&& o);
	vec3 hadamardProd(const vec3& o)const;
	vec3& bangHadamardProd(const vec3& o);
	void bangMult(v_t f);
	vec3 mult(v_t f)const;
	void bangAdd(v_t f);
	vec3 add(v_t f)const;
	void bangAdd(const vec3& f);
	vec3 add(const vec3& f)const;
	void bangSub(const vec3& f);
	vec3 sub(const vec3& f)const;
	v_t mult(const vec3& o)const;
	vec3 crossMult(const vec3& o)const;
	void normalize();
	vec3 normalized()const;
	vec3 operator&(const vec3& o)const;
	vec3& operator&=(const vec3& o);
	vec3 operator+(const vec3& o)const;
	vec3& operator+=(const vec3& o);
	vec3 operator-(const vec3& o)const;
	vec3& operator-=(const vec3& o);
	vec3 operator*(v_t f)const;
	vec3 operator%(const vec3& o)const;
	vec3& operator*=(v_t f);
	bool operator==(const vec3& o)const;
	bool operator==(v_t o)const;
	bool operator!=(const vec3& o)const;
	bool operator!=(v_t o)const;
	vec3& operator=(const vec3& o);
	vec3& operator=(vec3&& o);
	vec3 operator!()const;
	v_t operator*(const vec3& f)const;
	v_t normsq()const;
	v_t norm()const;
	friend std::ostream& operator<<(std::ostream& out,const vec3& o){
		out << "(" << o.x << ", " << o.y << ", " << o.z << ")";
		return out;
	}
};
#endif