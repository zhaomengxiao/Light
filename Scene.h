#pragma once

#include <vector>
#include "SDF.h"
#include "macrodef.h"



class SignedDistanceField;
using SDF = SignedDistanceField;

/**
* \brief constructive solid geometry
* 以形状点集的布尔操作来表示模型。
* 3个基本运算为:
* 并集（union）
* 交集（intersection）
* 相对补集（relative complement，或称为 set difference）：
*/
enum class BoolOp
{
	UNION_OP,
	INTERSECT_OP,
	SUBTRACT_OP,
	SIZE_OP
};




inline const char* to_string(const BoolOp e)
{
	switch (e)
	{
	case BoolOp::UNION_OP: return "unionOp";
	case BoolOp::INTERSECT_OP: return "intersectOp";
	case BoolOp::SUBTRACT_OP: return "subtractOp";
	case BoolOp::SIZE_OP: return "size_op";
	default: return "unknown";
	}
}

class Scene
{
public:

	Scene(unsigned width, unsigned height, unsigned sample_n)
		: width_(width),
		  height_(height),
		  sample_n_(sample_n)
	{
	}

	Scene& addSDF(SDF& sdf,BoolOp bool_op);
	
	Result process(float x, float y);

	float trace(float ox, float oy, float dx, float dy);

	float sample(float x, float y);
private:
	std::vector<std::pair<SDF&, BoolOp>>  sdf_list_;
	unsigned width_ { 100 };

	unsigned height_ {100};

	unsigned sample_n_ {64};

	unsigned max_step_ {10};

	float max_distance_ {5.0f};

	float epsilon_ {1e-6f};
};
