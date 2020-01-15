#pragma once

#include <vector>



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


struct Result
{
	float sd;
	float emissive;
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

	//void addSDF(SDF sdf);
	Scene& addSDF(SDF* sdf,BoolOp bool_op);
	SDF* process(float x, float y);
private:
	std::vector<SDF*>  sdf_list_;
};
