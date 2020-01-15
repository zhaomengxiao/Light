#include <math.h>
#include "SDF.h"


SignedDistanceField* SignedDistanceField::unionOp(SignedDistanceField* another)
{
	return this->sd < another->sd ? this : another;
}

SignedDistanceField* SignedDistanceField::intersectOp(SignedDistanceField* another)
{
	const auto r = this->sd > another->sd ? another : this;
	r->sd = this->sd > another->sd ? this->sd : another->sd;
	return r;
}

SignedDistanceField* SignedDistanceField::subtractOp(SignedDistanceField* another)
{
	const auto r = this;
	r->sd = (this->sd > -another->sd) ? this->sd : -another->sd;
	return r;
}

float PointSDF::SD(float x, float y)
{
	const float ux = x - x_;
	const float uy = y - y_;
	return sd = sqrtf(ux * ux + uy * uy); 
}

float CircleSDF::SD(float x, float y)
{
	const float ux = x - center_x_;
	const float uy = y - center_y_;
	return sd = sqrtf(ux * ux + uy * uy) - radius_;
}
