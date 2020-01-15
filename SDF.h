#pragma once


/**
 * \brief 带符号距离场, SDF
 */
class SignedDistanceField
{
public:

	SignedDistanceField(const float emissive)
		: sd(0), emissive(emissive)
	{
	}

	virtual ~SignedDistanceField() = default;
	
	virtual float SD(float x, float y) { return sd; }

	float Emissive() const { return emissive; }

	SignedDistanceField* unionOp(SignedDistanceField* another);

	SignedDistanceField* intersectOp(SignedDistanceField* another);

	SignedDistanceField* subtractOp(SignedDistanceField* another);

	float sd;
	float emissive;


};

class PointSDF : public SignedDistanceField
{
public:

	/**
	 * \brief 
	 * \param emissive 自发光强度
	 * \param x 点X坐标
	 * \param y 点Y坐标
	 */
	PointSDF(float emissive, float x, float y)
		: SignedDistanceField(emissive),
		  x_(x),
		  y_(y)
	{
	}

	float SD(float x, float y) override;
private:
	float x_;
	float y_;
};


class CircleSDF : public SignedDistanceField
{
public:
	
	/**
	 * \brief 
	 * \param emissive  :自发光强度
	 * \param center_x  :圆心X坐标
	 * \param center_y  :圆心Y坐标
	 * \param radius    :圆周
	 */
	CircleSDF(float emissive, float center_x, float center_y, float radius)
		: SignedDistanceField(emissive),
		  center_x_(center_x),
		  center_y_(center_y),
		  radius_(radius)
	{
	}

	float SD(float x, float y) override;

private:
	float center_x_;
	float center_y_;
	float radius_;
};




