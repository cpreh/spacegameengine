#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_SNIP_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_SNIP_HPP_INCLUDED

#include <sge/projectile/triangulation/detail/point_inside_triangle.hpp>

namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace detail
{
template<typename PointContainer,typename IndexContainer>
bool 
snip(
	PointContainer const &contour,
	typename PointContainer::size_type const u,
	typename PointContainer::size_type const v,
	typename PointContainer::size_type const w,
	typename PointContainer::size_type const n,
	IndexContainer const &V,
	typename PointContainer::value_type::value_type const epsilon)
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

	vector a,b,c,p;

  a[0] = contour[V[u]][0];
  a[1] = contour[V[u]][1];

  b[0] = contour[V[v]][0];
  b[1] = contour[V[v]][1];

  c[0] = contour[V[w]][0];
  c[1] = contour[V[w]][1];

  if(epsilon > (((b[0]-a[0])*(c[1]-a[1])) - ((b[1]-a[1])*(c[0]-a[0])))) 
		return false;

  for(size_type i = 0; i<n; i++)
  {
    if((i == u) || (i == v) || (i == w)) 
			continue;

    p[0] = contour[V[i]][0];
    p[1] = contour[V[i]][1];

    if(sge::projectile::triangulation::detail::point_inside_triangle(a,b,c,p)) 
			return false;
  }

  return true;
}
}
}
}
}

#endif
