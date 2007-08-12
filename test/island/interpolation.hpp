#ifndef INTERPOLATION_HPP_INCLUDED
#define INTERPOLATION_HPP_INCLUDED

template<typename FLOAT>
struct linear_interpolation
{
	FLOAT operator()(const FLOAT a,const FLOAT b, const FLOAT x) const
	{
		return a*(FLOAT(1)-x)+x*b;
	}
};

#endif
