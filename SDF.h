#pragma once

struct Result
{
	Result() = default;

	Result(float sd, float emissive)
		: sd(sd),
		  emissive(emissive)
	{
	}

	float sd{0};
	float emissive{0};

	static Result unionOp(Result a, Result b)
	{
		return a.sd < b.sd ? a : b;

	}

	static Result intersectOp(Result a, Result b)
	{
		Result r = a.sd > b.sd ? b : a;
		r.sd = a.sd > b.sd ? a.sd : b.sd;
		return r;

	}

	static Result subtractOp(Result a, Result b)
	{
		Result r = a;
		r.sd = (a.sd > -b.sd) ? a.sd : -b.sd;
		return r;
	}
};

/**
 * \brief 带符号距离场, SDF
 */
class SignedDistanceField
{
public:

	explicit SignedDistanceField(const float emissive)
		: result{ 0, emissive }
	{
	}

	virtual ~SignedDistanceField() = default;
	
	virtual float SD(float x, float y) { return result.sd; }

	float Emissive() const { return result.emissive; }

	Result getResult() const { return result; }

	Result result;
};

class PlaneSDF : public SignedDistanceField
{
public:
	/**
	 * \brief 平面SDF
	 * \param emissive 自发光强度
	 * \param px 点x
	 * \param py 点y
	 * \param nx 法线x
	 * \param ny 法线y
	 */
	PlaneSDF(float emissive, float px, float py, float nx, float ny)
		: SignedDistanceField(emissive),
		  px_(px),
		  py_(py),
		  nx_(nx),
		  ny_(ny)
	{
	}

	float SD(float x, float y) override;
private:
	float px_;
	float py_;
	float nx_;
	float ny_;
};

class PointSDF : public SignedDistanceField
{
public:

	/**
	 * \brief 点SDF
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
	 * \brief 圆SDF
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




