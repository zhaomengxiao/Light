#include "Scene.h"
#include "SDF.h"
#include <iostream>


Scene& Scene::addSDF(SDF& sdf, const BoolOp bool_op)
{
	/*switch (bool_op)
	{
	case BoolOp::UNION_OP:
		result_ = result_->unionOp(sdf);
		return *this;
		break;
	case BoolOp::INTERSECT_OP:
		result_ = result_->intersectOp(sdf);
		return *this;
		break;

	case BoolOp::SUBTRACT_OP:
		result_ = result_->subtractOp(sdf);
		return *this;
		break;
	default:
		std::cout<<"addSDF error, no such Op \n";
		return *this;
	}*/
	sdf_list_.push_back({ sdf,bool_op });
	return *this;
}

Result Scene::process(float x, float y)
{
	Result res;
	if (!sdf_list_.empty())
	{
		SDF* base = &sdf_list_[0].first;
		base->SD(x, y);
		res = base->result;
		for (int i = 1; i < sdf_list_.size(); ++i)
		{
			SDF* another = &sdf_list_[i].first;
			another->SD(x, y);
			base->SD(x, y);
			switch (sdf_list_[i].second)
			{
			case BoolOp::UNION_OP:
				res = Result::unionOp(res, another->result);
			break;
			case BoolOp::INTERSECT_OP:
				res = Result::intersectOp(res, another->result);
			break;
			case BoolOp::SUBTRACT_OP:
				res = Result::subtractOp(res, another->result);
			break;
			default:
			std::cout<<"addSDF error, no such Op \n";
			}			
		}
	}
	return res;
}

float Scene::trace(float ox, float oy, float dx, float dy)
{
	float t = 0.0f;
	for (unsigned i = 0; i < max_step_ && t < max_distance_; i++)
	{
		const auto r = process(ox + dx * t, oy + dy * t);
		if (r.sd < epsilon_)
			return r.emissive;
		t += r.sd;
	}
	return 0.0f;
}

float Scene::sample(float x, float y)
{
	auto sum = 0.0f;
	for (unsigned i = 0; i < sample_n_; i++)
	{
		//float a = TWO_PI * rand() / RAND_MAX;
		//float a = TWO_PI * i / 64;
		auto a = TWO_PI * (i + float(rand()) / RAND_MAX) / sample_n_;
		sum += trace(x, y, cosf(a), sinf(a));
	}
	return sum / sample_n_;
}
