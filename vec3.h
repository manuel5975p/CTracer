#ifndef VEC3_H
#define VEC3_H
#include <iostream>
#include <random>
#include <cmath>
#define M_PI	3.14159265358979323846
#define M_PI_2	1.57079632679489661923
#define M_PI_4	0.785398163397448309616
#define M_1_PI	0.318309886183790671538
#define M_2_PI	0.636619772367581343076
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2	1.41421356237309504880
#define M_SQRT1_2	0.707106781186547524401
#define M_E	2.71828182845904523536
#define M_LOG2E	1.44269504088896340736
#define M_LOG10E	0.434294481903251827651
#define M_LN2	0.693147180559945309417
#define M_LN10	2.30258509299404568402
using v_t = double;
struct vec3{
	v_t x,y,z;
	vec3();
	vec3(v_t a);
	vec3(v_t _x,v_t _y,v_t _z);
	vec3(std::mt19937_64& eng);
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
	vec3 ortho(std::mt19937_64& gen)const;
	vec3 randomHemisphere(std::mt19937_64& gen)const;
	vec3 operator&(const vec3& o)const;
	vec3& operator&=(const vec3& o);
	vec3 operator+(const vec3& o)const;
	vec3& operator+=(const vec3& o);
	vec3 operator-(const vec3& o)const;
	vec3 operator-()const;
	vec3& operator-=(const vec3& o);
	vec3 operator*(v_t f)const;
	vec3 operator%(const vec3& o)const;
	vec3& operator*=(v_t f);
	vec3 operator/(v_t f)const;
	vec3& operator/=(v_t f);
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