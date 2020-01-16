#include "Scene.h"
#include "SDF.h"


Scene& Scene::addSDF(SDF* sdf, const BoolOp bool_op)
{
	/*switch (bool_op)
	{
	case BoolOp::UNION_OP:
		result_ = result_->unionOp(sdf);
		return *this;
		break;*/
	/*case BoolOp::INTERSECT_OP:
		result_ = result_->intersectOp(sdf);
		return *this;
		break;

	case BoolOp::SUBTRACT_OP:
		result_ = result_->subtractOp(sdf);
		return *this;
		break;
	default:
		std::cout<<"addSDF error, no such Op \n";
		return *this;*/
	//}
	sdf_list_.push_back(sdf);
	return *this;
}

Result Scene::process(float x, float y)
{
	Result res;
	if (!sdf_list_.empty())
	{
		SDF* base = sdf_list_[0];
		base->SD(x, y);
		res = base->result;
		for (int i = 1; i < sdf_list_.size(); ++i)
		{
			SDF* another = sdf_list_[i];
			//SDF* base = sdf_list_[i - 1];
			another->SD(x, y);
			base->SD(x, y);
			res = Result::unionOp(res,another->result);
		}
	}
	
	/*for (auto sdf : sdf_list_)
	{
		sdf->SD(x, y);
	}
	Result res = Result::unionOp(sdf_list_[0]->result, sdf_list_[1]->result);
	res = Result::unionOp(res, sdf_list_[2]->result);*/
	return res;
}
