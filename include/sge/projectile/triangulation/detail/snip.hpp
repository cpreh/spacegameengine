/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_PROJECTILE_TRIANGULATION_DETAIL_SNIP_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_DETAIL_SNIP_HPP_INCLUDED

#include <sge/projectile/triangulation/detail/point_inside_triangle.hpp>
#include <boost/mpl/identity.hpp>

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
	// hack VC++ constructor type bug
	typename boost::mpl::identity<
		typename PointContainer::value_type
	>::type::value_type const epsilon)
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
