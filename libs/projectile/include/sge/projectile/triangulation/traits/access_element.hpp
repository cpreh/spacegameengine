//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGULATION_TRAITS_ACCESS_ELEMENT_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRAITS_ACCESS_ELEMENT_HPP_INCLUDED

#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/traits/access_element_fwd.hpp>


namespace sge::projectile::triangulation::traits
{

template<
	typename Vertex
>
struct access_element<
	Vertex,
	sge::projectile::triangulation::default_tag
>
{
	static
	typename Vertex::value_type
	execute(
		Vertex const &_vertex,
		typename Vertex::size_type const _index
	)
	{
		return
			_vertex.get_unsafe(
				_index
			);
	}
};

}

#endif
