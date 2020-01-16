#include <cmath>
#include "SDF.h"


float PlaneSDF::SD(float x, float y)
{
	return result.sd = (x - px_) * nx_ + (y - py_) * ny_;
}

float PointSDF::SD(float x, float y)
{
	const auto ux = x - x_;
	const float uy = y - y_;
	return result.sd = sqrtf(ux * ux + uy * uy); 
}

float CircleSDF::SD(float x, float y)
{
	const float ux = x - center_x_;
	const float uy = y - center_y_;
	return result.sd = sqrtf(ux * ux + uy * uy) - radius_;
}
