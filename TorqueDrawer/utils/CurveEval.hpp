#pragma once

#include <vector>

class InterpCurveConstant
{
public:
	struct ICPoint
	{
		double inV;
		double outV;
	};

protected:
	std::vector< ICPoint > Points;

public:

	//constructor
	InterpCurveConstant() = default;
	//InterpCurveConstant( ... ) {}

	//destructor
	//-------------------------

	size_t	AddPoint(const double inVal, const double outVal);
	double	Eval(const double InVal, const double& Default) const;

	void print(std::ostream& out);
	void dump(std::ostream& out);
	void load(std::ostream& out);
	void save(std::ostream& out);
};



inline size_t	InterpCurveConstant::AddPoint(const double inVal, const double outVal)
{
	auto& it = Points.begin();
	for (; it != Points.end() && it->inV < inVal; ++it);	//find nearest.
	Points.insert(it, ICPoint{ inVal, outVal });
	return Points.end() - it;
}

inline double InterpCurveConstant::Eval(const double InVal, const double& Default) const
{
	size_t NumP = Points.size();

	if (NumP == 0) { return Default; }
	if (NumP < 2 || (InVal <= Points[0].inV)) { return Points[0].outV; }
	if (InVal >= Points[NumP - 1].inV) { return Points[NumP - 1].outV; }

	//linear search.
	for (size_t i = 1u; i<NumP; i++)
	{
		if (InVal < Points[i].inV)
		{
			double dist = Points[i].inV - Points[i - 1].inV;

			if (dist > 0.0)
			{
				double alpha = (InVal - Points[i - 1].inV) / dist;

				return (Points[i - 1].outV * alpha) + (Points[i].outV * (1.0 - alpha));
			}
			else
				return Points[i - 1].outV;
		}
	}
	return Points[NumP - 1].outV;
}


inline void InterpCurveConstant::print(std::ostream& out) {}
inline void InterpCurveConstant::dump(std::ostream& out) {}
inline void InterpCurveConstant::load(std::ostream& out) {}
inline void InterpCurveConstant::save(std::ostream& out) {}