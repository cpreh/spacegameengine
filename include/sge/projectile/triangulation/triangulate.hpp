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


#ifndef SGE_PROJECTILE_TRIANGULATION_TRIANGULATE_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRIANGULATE_HPP_INCLUDED

#include <sge/projectile/triangulation/detail/area.hpp>
#include <sge/projectile/triangulation/detail/snip.hpp>
#include <fcppt/container/raw_vector.hpp>
#include <fcppt/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/algorithm_ext/iota.hpp>

namespace sge
{
namespace projectile
{
namespace triangulation
{

template<typename ResultContainer,typename ContourContainer>
ResultContainer const
triangulate(
	ContourContainer const &contour,
	// hack VC++ constructor type bug
	typename boost::mpl::identity<
		typename ContourContainer::value_type
	>::type::value_type const epsilon)
{
	typedef typename
	ContourContainer::size_type
	size_type;

	typedef typename
	ContourContainer::value_type
	vector;

	typedef typename
	vector::value_type
	scalar;

	FCPPT_ASSERT(
		contour.size() >= static_cast<size_type>(3));

	fcppt::container::raw_vector<size_type> V(
		contour.size());

	/* we want a counter-clockwise polygon in V */
	if(static_cast<scalar>(0.0) < sge::projectile::triangulation::detail::area(contour))
	{
		boost::iota(
			V,
			static_cast<size_type>(
				0));
	}
	else
	{
		for(size_type v = 0; v < contour.size(); v++) 
			V[v] = static_cast<size_type>((contour.size()-1)-v);
	}

	size_type nv = 
		contour.size();

	/*  remove nv-2 Vertices, creating 1 triangle every time */
	size_type count = 
		static_cast<size_type>(
			2*nv);   /* error detection */

	ResultContainer result;

	for(
		size_type 
			m = 
				0, 
			v = 
				static_cast<size_type>(
					nv-1); 
			nv>2u; )
	{
		FCPPT_ASSERT(
			0 < count);

		--count;

		/* three consecutive vertices in current polygon, <u,v,w> */
		size_type u = v  ; if (nv <= u) u = 0;     /* previous */
		v = u+1; if (nv <= v) v = 0;     /* new v    */
		size_type w = v+1; if (nv <= w) w = 0;     /* next     */

		if(sge::projectile::triangulation::detail::snip(contour,u,v,w,nv,V,epsilon))
		{
			size_type a,b,c,s,t;

			/* true names of the vertices */
			a = V[u]; b = V[v]; c = V[w];

			typename ResultContainer::value_type new_triangle;
			new_triangle[0] = contour[a];
			new_triangle[1] = contour[b];
			new_triangle[2] = contour[c];
			result.insert(
				result.end(),
				new_triangle);

			m++;

			/* remove v from remaining polygon */
			for(s=v,t=v+1;t<nv;s++,t++) V[s] = V[t]; nv--;

			/* resest error detection counter */
			count = 2*nv;
		}
	}
	return result;
}
}
}
}

#endif
