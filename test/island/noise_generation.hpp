#ifndef NOISE_GENERATION_INCLUDED_HPP
#define NOISE_GENERATION_INCLUDED_HPP

#include <cassert>
#include <cstdlib>
#include <vector>

#include "../../src/math/utility.hpp"

template<typename FLOAT,typename COORD>
struct standard_noise_generation
{
	standard_noise_generation() {}
	standard_noise_generation(const COORD,const COORD) {}
	void reset() {};

	FLOAT operator()(COORD x,COORD y) const 
	{
		COORD n = x + y * COORD(57); n = (n<<13) ^ n;
		return sge::math::abs((FLOAT(1.0) - ((n * (n * n * COORD(15731) + COORD(789221)) + COORD(1376312589)) & COORD(0x7fffffff)) / FLOAT(1073741824.0)));
	}
};

template<typename FLOAT,typename COORD>
struct stdlib_noise_generation
{
	typedef std::vector<FLOAT> inner_type;
	typedef std::vector<inner_type> outer_type;
	outer_type pairs;

	stdlib_noise_generation() {}
	stdlib_noise_generation(const COORD w,const COORD h) { reset(w,h); }

	void reset(const COORD w,const COORD h)
	{
		pairs.resize(w+1);
		for (typename outer_type::iterator i = pairs.begin(); i != pairs.end(); ++i)
		{
			i->resize(h+1);
			std::fill(i->begin(),i->end(),FLOAT(-1));
		}
	}
	
	FLOAT operator()(const COORD x,const COORD y)
	{
		assert(x >= 0 && y >= 0);
		assert(x < pairs.size() || y < pairs[x].size());

		if (pairs[x][y] != FLOAT(-1))
			return pairs[x][y];

		return pairs[x][y] = FLOAT(std::rand() / (RAND_MAX + 1.0));
	}
};

#endif
