#define _CRT_SECURE_NO_WARNINGS
#include"PathTracing.h"
//#include"PTVec.h"
#include"PTCamera.h"
#include<memory>
#include<glm/glm.hpp>
#include<iostream>
#include"PTrandom.h"
#include"PTMaterial.h"
#include"hittable.h"
#include"PTTexture.h"
#include"hittable/Rect.h"
#include"Renderer.h"

using namespace PT;
class PT::Material;
using std::make_shared;
using std::shared_ptr;


void cornell_box(std::shared_ptr<Renderer>& renderer) {
	std::shared_ptr<Camera> camera = std::make_shared<Camera>
		(vec3(278.0f,278.0f,-800.0f),vec3(278.0f,278.0f,0.0f),vec3(0,1,0),40.0,
		600,600);
	renderer->addCam(camera);
	
	auto red = make_shared<Lambertian>(vec3(.65, .05, .05));
	auto white = make_shared<Lambertian>(vec3(.73, .73, .73));
	auto green = make_shared<Lambertian>(vec3(.12, .45, .15));
	auto light = make_shared<DiffuseLight>(vec3(1.0f, 1.0f, 1.0f) * 15.0f);

	renderer->addObject(make_shared<yz_rect>(0, 555, 0, 555, 555, green));
	renderer->addObject(make_shared<yz_rect>(0, 555, 0, 555, 0, red));
	renderer->addObject(make_shared<xz_rect>(0, 343-213, 555- (332-227), 555, 554, light));
	renderer->addObject(make_shared<xz_rect>(0, 555, 0, 555, 0, white));
	renderer->addObject(make_shared<xz_rect>(0, 555, 0, 555, 555, white));
	renderer->addObject(make_shared<xy_rect>(0, 555, 0, 555, 555, white));
}

void PT::render() {
	srand(time(0));
	int samples = 50;
	int max_depth = 20;

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(samples,max_depth);

	// world 
	cornell_box(renderer);

	int threadNum = 9;
	renderer->render(threadNum);
	renderer->writeToFile("./out.ppm");
}

