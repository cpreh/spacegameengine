//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_TRIANGULATION_TRAITS_SCALAR_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRAITS_SCALAR_HPP_INCLUDED

#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/traits/scalar_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace traits
{

template<
	typename Vertex
>
struct scalar<
	Vertex,
	sge::projectile::triangulation::default_tag
>
{
	typedef typename Vertex::value_type type;
};

}
}
}
}

#endif
