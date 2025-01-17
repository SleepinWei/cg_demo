#pragma once
#include "../hittable.h"
#include <glm/glm.hpp>
#include <memory>

class hittable;
class Ray;
class AABB;

class TransHittable : public hittable
{
public:
	TransHittable();
	TransHittable(std::shared_ptr<hittable> object, glm::mat4 model);
	~TransHittable();

	virtual bool hit(const Ray &r, double t_min, double t_max, hit_record &rec) const override;
	virtual bool bounding_box(double time0, double time1, AABB &output_box) const override;
	virtual void addTexture(std::shared_ptr<PTMaterial> &mat);

public:
	std::shared_ptr<hittable> object;
	glm::mat4 model;
};
