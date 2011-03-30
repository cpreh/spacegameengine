#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_AREA_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_AREA_HPP_INCLUDED

#include <boost/mpl/identity.hpp>

namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace detail
{
// This function works on a variety of types. The requirements are:
//
// - PointContainer needs to have ::size_type
// - PointContainer needs to have ::value_type
// - PointContainer::value_type needs to have ::value_type
// - PointContainer::value_type needs to have an operator[]
// - PointContainer::value_type::value_type needs to be static_castable from an integer literal
// - PointContainer::value_type::value_type needs to be a ring
template<typename PointContainer>
typename
// hack VC++ constructor type bug
boost::mpl::identity<
	typename PointContainer::value_type
>::type::value_type
area(
	PointContainer const &contour)
{
	typedef typename
	PointContainer::size_type
	size_type;

	typedef typename
	PointContainer::value_type
	vector;

	typedef typename
	vector::value_type
	scalar;

	scalar result = 
		static_cast<scalar>(
			0);

  for(
		size_type 
			p = 
				static_cast<size_type>(
					contour.size()-1),
			q=
				static_cast<size_type>(
					0); 
			q < contour.size(); 
			p=q++)
    result = 
			static_cast<scalar>(
				result + contour[p][0]*contour[q][1] - contour[q][0]*contour[p][1]);

  return 
		static_cast<scalar>(
			result/static_cast<scalar>(2));
}
}
}
}
}

#endif
