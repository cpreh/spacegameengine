//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_PERMUTATE_COMPARE_HPP_INCLUDED
#define SGE_IMAGE_COLOR_IMPL_DYNAMIC_ALGORITHM_CAC_PERMUTATE_COMPARE_HPP_INCLUDED

#include <fcppt/algorithm/contains.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace impl
{
namespace dynamic
{
namespace algorithm
{
namespace cac
{

template<
	typename Layout
>
bool
permutate_compare(
	Layout const &_layout1,
	Layout const &_layout2
)
{
	// TODO(philipp): Algorithm
	for(
		auto const &elem
		:
		_layout1
	)
	{
		if(
			!fcppt::algorithm::contains(
				_layout2,
				elem
			)
		)
		{
			return
				false;
		}
	}

	return
		true;
}

}
}
}
}
}
}
}

#endif
