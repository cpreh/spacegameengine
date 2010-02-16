#ifndef SGE_CONSOLE_NEXT_OR_LAST_HPP_INCLUDED
#define SGE_CONSOLE_NEXT_OR_LAST_HPP_INCLUDED

#include <fcppt/math/is_negative.hpp>
#include <boost/next_prior.hpp>
#include <fcppt/assert.hpp>
#include <algorithm>
#include <iterator>

namespace sge
{
namespace console
{
template
<
	typename It1,
	typename It2,
	typename Distance
>
It1 const 
next_or_last(
	It1 it,
	It2 const last,
	Distance const u)
{
	typedef typename
	std::iterator_traits<It1>::difference_type
	difference_type;
	
	difference_type const d = 
		std::distance(
			it,
			last);
	
	FCPPT_ASSERT(
		!fcppt::math::is_negative(
			d));
			
	return 
		boost::next(
			it,
			std::min(
				static_cast<difference_type>(
					u),
				d));
}
}
}

#endif