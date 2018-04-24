#include "vec3.h"
#include "Ray.h"
#include "objects.h"
#include "bmp.h"
#include <vector>
vec3 ambient(0,0,1);
sphere s(vec3(0,0,2),0.7);
light_sphere ls(vec3(0,4,2),2);
light_sphere ls2(vec3(-50,1,2),20);
vec3 trace(const ray& init){
	ray run = init;
	for(int i = 0;i < 20;i++){
		if((s >> run) != 0){
			ray prun = s.reflectingRay(run);
			run = prun;
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
		else{
			run.colorStack.push(ambient);
			break;
		}
	}
	vec3 col = run.colorStack.top();
	run.colorStack.pop();
	while(!run.colorStack.empty()){
		col &= run.colorStack.top();
		run.colorStack.pop();
	}
	return col;
}
int main(){
	s.setColor(0.5,0.6,0.6);
	ls.setColor(1,0,0.5);
	ls2.setColor(1,0.3,0);
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
			
			pixels[yi * 512 + xi] = accum;
			xi++;
		}
		yi++;
	}
	drawbmp("ratras.bmp", pixels);
}