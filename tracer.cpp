#include "vec3.h"
#include "ray.h"
#include "objects.h"
#include "bmp.h"
#include <time.h>
#include <vector>
#include <omp.h>
#include "util.h"
std::mt19937_64 gen(time(NULL));
vec3 ambient(0.2,0.2,0.2);
sphere s(vec3(0,0,2),0.7);
sphere s2(vec3(1.2,-1.2,2),0.7);
sphere s3(vec3(-2,-1.2,1.7),1);
light_sphere ls(vec3(0,3,-5),1);
light_sphere ls2(vec3(-20,1,2),4);
light_sphere ls3(vec3(0,1,-50),25);
vec3 trace(const ray& init){
	ray run = init;
	for(int i = 0;i < 20;i++){
		if((s >> run) != 0){
			run = s.reflectingRay(run);
			run.colorStack.push(s.color);
			continue;
		}
		else if((s2 >> run) != 0){
			run = s2.reflectingRay(run);
			run.colorStack.push(s2.color);
			continue;
		}
		else if((s3 >> run) != 0){
			run = s3.reflectingRay(run);
			run.colorStack.push(s3.color);
			continue;
		}
		else if((ls >> run) != 0){
			run.colorStack.push(ls.color);
			break;
		}
		else if((ls2 >> run) != 0){
			run.colorStack.push(ls2.color);
			break;
		}
		else if((ls3 >> run) != 0){
			run.colorStack.push(ls3.color);
			break;
		}
		else{
			run.colorStack.push(ambient);
			break;
		}
	}
	vec3 col(1);
	while(!run.colorStack.empty()){
		col &= run.colorStack.top();
		run.colorStack.pop();
	}
	return col;
}
#ifndef rpp
#define rpp 100
#endif
/*int main(){
	sphere s(vec3(0,0,0), 1);
	ray r(vec3(0.5,5,0.5),vec3(0,-1,0));
	std::cout << s.intersectionPoint(r).normsq() << std::endl;
}*/
int main(){
	s.setColor(0.8,0.8,0.8);
	s2.setColor(1,0,0);
	s3.setColor(0.97,0.97,0.97);
	s3.diffuse = false;
	ls.setColor(8,8,0);
	ls2.setColor(0,1,1);
	ls3.setColor(1,1,1);
	std::vector<vec3> pixels(512 * 512);
	int xi = 0,yi = 0;
	std::stopwatch sw;
	
	for(double x = -1;x < 1;x += 1.0 / 256){
		xi = 0;
		for(double y = -1;y < 1;y += 1.0 / 256){
			ray curr(vec3(0,0,-2),vec3(y,x,1));
			vec3 accum_[4];
			#pragma omp parallel for
			for(int i = 0;i < rpp;i++){
				vec3 color = trace(curr);
				if(color == ambient)i = rpp;
				accum_[omp_get_thread_num()] += color;
			}
			vec3 accum = accum_[0] + accum_[1] + accum_[2] + accum_[3];
			pixels[yi * 512 + xi] = accum * (1.0 / rpp);
			xi++;
		}
		yi++;
	}
	std::cout << sw.elapsed() / 1000000 << "ms sind vergangen." << std::endl;
	drawbmp("ratras.bmp", pixels);
}
