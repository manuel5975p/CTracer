#include "vec3.h"
#include "Ray.h"
#include "objects.h"
#include "bmp.h"
#include <vector>
vec3 ambient(0,0,1);
sphere s(vec3(0,0,2),0.7);
light_sphere ls(vec3(0,4,2),2);
vec3 trace(const ray& init){
	ray run = init;
	for(int i = 0;i < 20;i++){
		if((s >> run) != 0){
			//if(((s >> run) - s.loc).norm() >= 0.69 && ((s >> run) - s.loc).norm() <= 0.71)
			//std::cout << ((s >> run) - s.loc).norm() << " ";
			ray prun = s.reflectingRay(run);
			if(i > 3){
			}
			run = prun;
			continue;
		}
		else if((ls >> run) != 0){
			run.colorStack.push(ls.color);
			break;
		}
		else{
			run.colorStack.push(ambient);
			break;
		}
	}
	std::cout << run.colorStack.size() << " ";
	vec3 col = run.colorStack.top();
	run.colorStack.pop();
	while(!run.colorStack.empty()){
		col &= run.colorStack.top();
		run.colorStack.pop();
	}
	return col;
}
int mainr(){
	s.setColor(0.5,0.6,0.6);
	ls.setColor(0.4,1,0.5);
	ray r(vec3(0,0,-2), vec3(0,0,2));
	std::cout << (s >> r) << std::endl;
	ray r2;
	r2 = s.reflectingRay(r);
	std::cout << (r2 = s.reflectingRay(r,true)) << std::endl;
	std::cout << s.reflectingRay(r2,true);
	return 0;
}
int main(){
	s.setColor(0.5,0.6,0.6);
	ls.setColor(0.4,1,0.5);
	std::vector<vec3> pixels(512 * 512);
	int xi = 0,yi = 0;
	for(double x = -1;x < 1;x += 1.0 / 256){
		xi = 0;
		for(double y = -1;y < 1;y += 1.0 / 256){
			ray curr(vec3(0,0,-2),vec3(y,x,1));
			vec3 accum;
			for(int i = 0;i < 1;i++){
				vec3 color = trace(curr);
				accum += color;
			}
			//if(accum.norm() > 0.2)
			//std::cout << accum << std::endl;
			//std::cout << xi << " ";
			/*if((yi * 512 + xi) >= 512 * 512){
				goto end;
			}*/
			pixels[yi * 512 + xi] = accum;
			xi++;
		}
		yi++;
	}
	drawbmp("ratras.bmp", pixels);
}