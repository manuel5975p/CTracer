#include "vec3.h"
std::uniform_real_distribution<v_t> dist(-1,1);
std::uniform_real_distribution<v_t> PI_2_dist(0,M_PI_2);
std::uniform_real_distribution<v_t> PI_dist(0,M_PI);
std::uniform_real_distribution<v_t> TWO_PI_dist(0,M_PI * 2);
vec3::vec3(v_t _x,v_t _y,v_t _z) : x(_x),y(_y),z(_z){
	
}
vec3::vec3() : x(0),y(0),z(0){
	
}
vec3::vec3(std::mt19937_64& gen){
	x = dist(gen);
	y = dist(gen);
	z = dist(gen);
	normalize();
}
vec3::vec3(v_t a) : x(a),y(a),z(a){
	
}
vec3::vec3(const vec3& o) : x(o.x),y(o.y),z(o.z){
	
}
vec3::vec3(vec3&& o) : x(o.x),y(o.y),z(o.z){
	
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
vec3 vec3::ortho(std::mt19937_64& gen)const{
	vec3 tn = normalized();
	vec3 ret(gen);
	while(tn * ret < 0.01){
		ret = vec3(gen);
	}
	return !(tn % ret);
}
vec3 vec3::randomHemisphere(std::mt19937_64& gen)const{
	vec3 orth = this->ortho(gen);
	v_t theta = PI_2_dist(gen);
	return (orth * std::cos(theta)) + (this->normalized() * std::sin(theta));
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
	return vec3(x / f,y / f,z / f);
}
vec3& vec3::operator/=(v_t f){
	x /= f;
	y /= f;
	z /= f;
	return *this;
}
bool vec3::operator==(const vec3& o)const{
	return x == o.x && y == o.y && z == o.z;
}
bool vec3::operator==(v_t o)const{
	return o == 0 && x == 0 && y == 0 && z == 0;
}
bool vec3::operator!=(const vec3& o)const{
	return x != o.x || y != o.y || z != o.z;
}
bool vec3::operator!=(v_t o)const{
	return o != 0 || x != 0 || y != 0 || z != 0;
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