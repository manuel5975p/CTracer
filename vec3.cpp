#include <cassert>
#include "vec3.h"
std::uniform_real_distribution<v_t> dist(-1,1);
std::uniform_real_distribution<v_t> PI_2_dist(0,M_PI_2);
std::uniform_real_distribution<v_t> PI_dist(0,M_PI);
std::uniform_real_distribution<v_t> TWO_PI_dist(0,M_PI * 2);
unsigned long long rand_counter = 0;
vec3::vec3(v_t _x,v_t _y,v_t _z) : x(_x),y(_y),z(_z){
	
}
vec3::vec3() : x(0),y(0),z(0){
	
}
vec3::vec3(v_t a) : x(a),y(a),z(a){
	
}
vec3::vec3(const vec3& o) : x(o.x),y(o.y),z(o.z){
	
}
vec3::vec3(vec3&& o) : x(std::move(o.x)),y(std::move(o.y)),z(std::move(o.z)){
	
}

vec3::vec3(std::mt19937_64& gen){
	x = dist(gen);
	y = dist(gen);
	z = dist(gen);
	normalize();
}

void vec3::bangMult(v_t f){
	x *= f;
	y *= f;
	z *= f;
}
vec3 vec3::mult(v_t f) const{
	return vec3(x * f, y * f, z * f);
}
void vec3::bangAdd(v_t f){
	x += f;
	y += f;
	z += f;
}
void vec3::bangAdd(const vec3& f){
	x += f.x;
	y += f.y;
	z += f.z;
}
vec3 vec3::add(const vec3& f)const{
	return vec3(x + f.x,y + f.y,z + f.z);
}
vec3 vec3::hadamardProd(const vec3& o)const{
	return vec3(x * o.x,y * o.y,z * o.z);
}
vec3& vec3::bangHadamardProd(const vec3& o){
	x *= o.x;
	y *= o.y;
	z *= o.z;
	return *this;
}
void vec3::bangSub(const vec3& f){
	x -= f.x;
	y -= f.y;
	z -= f.z;
}
vec3 vec3::sub(const vec3& f)const{
	return vec3(x - f.x,y - f.y,z - f.z);
}
v_t vec3::mult(const vec3& o)const{
	return x * o.x + y * o.y + z * o.z;
}
vec3 vec3::crossMult(const vec3& o)const{
	return vec3(y * o.z - z * o.y,z * o.x - x * o.z, x * o.y - y * o.x);
}
void vec3::normalize(){
	v_t a = 1.0 / std::sqrt(x * x + y * y + z * z);
	x *= a;
	y *= a;
	z *= a;
}
vec3 vec3::normalized()const{
	v_t a = 1.0 / std::sqrt(x * x + y * y + z * z);
	return vec3(x * a ,y * a, z * a);
}
//PRE: *this must be normalized!
vec3 vec3::ortho(std::mt19937_64& gen)const{
	vec3 ret(gen);
	
	vec3 sample = (*this) % ret;
	sample.normalize();
	vec3 orthsample = (*this) % sample;
	orthsample.normalize();
	//std::cout << sample.normsq() << std::endl;
	v_t rnd = TWO_PI_dist(gen);
	//std::cout << ((sample * std::sin(rnd)) + (orthsample * std::cos(rnd))).normsq() << std::endl;
	return (sample * std::sin(rnd)) + (orthsample * std::cos(rnd));
	return !(*this % ret);
}
//PRE: *this must be normalized!
vec3 vec3::randomHemisphere(std::mt19937_64& gen)const{
	v_t theta;
	theta = PI_2_dist(gen);
	vec3 orth = this->ortho(gen);
	orth *= std::cos(theta);
	orth += (*this * std::sin(theta));
	return orth;
}
vec3 vec3::operator&(const vec3& o)const{
	return hadamardProd(o);
}
vec3& vec3::operator&=(const vec3& o){
	return bangHadamardProd(o);
}
vec3 vec3::operator+(const vec3& o)const{
	return add(o);
}
vec3& vec3::operator+=(const vec3& o){
	bangAdd(o);
	return *this;
}
vec3 vec3::operator-(const vec3& o)const{
	return sub(o);
}
vec3& vec3::operator-=(const vec3& o){
	bangSub(o);
	return *this;
}
vec3 vec3::operator*(v_t f)const{
	return mult(f);
}
vec3 vec3::operator%(const vec3& f)const{
	return crossMult(f);
}
v_t vec3::normsq() const{
	return x * x + y * y + z * z;
}
v_t vec3::norm()const{
	return std::sqrt(normsq());
}
vec3 vec3::operator-()const{
	return vec3(-x,-y,-z);
}
vec3& vec3::operator*=(v_t f){
	bangMult(f);
	return *this;
}
vec3 vec3::operator/(v_t f)const{
	f = ((v_t)1) / f;
	return vec3(x * f,y * f,z * f);
}
vec3& vec3::operator/=(v_t f){
	f = ((v_t)1) / f;
	x *= f;
	y *= f;
	z *= f;
	return *this;
}
bool vec3::operator==(const vec3& o)const{
	return x == o.x && y == o.y && z == o.z;
}
bool vec3::operator==(v_t o)const{
	assert(o == 0);
	return x == 0 && y == 0 && z == 0;
}
bool vec3::operator!=(const vec3& o)const{
	return x != o.x || y != o.y || z != o.z;
}
bool vec3::operator!=(v_t o)const{
	assert(o == 0);
	return x != 0 || y != 0 || z != 0;
}
vec3& vec3::operator=(const vec3& o){
	x = o.x;
	y = o.y;
	z = o.z;
	return *this;
}
vec3& vec3::operator=(vec3&& o){
	x = o.x;
	y = o.y;
	z = o.z;
	return *this;
}
v_t vec3::operator*(const vec3& f)const{
	return x * f.x + y * f.y + z * f.z;
}

vec3 vec3::operator!()const{
	return normalized();
}