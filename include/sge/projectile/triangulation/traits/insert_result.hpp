/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_PROJECTILE_TRIANGULATION_TRAITS_INSERT_RESULT_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRAITS_INSERT_RESULT_HPP_INCLUDED

#include <sge/projectile/triangulation/default_tag.hpp>
#include <sge/projectile/triangulation/traits/insert_result_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace traits
{

template<
	typename Container,
	typename Vertex
>
struct insert_result<
	Container,
	Vertex,
	sge::projectile::triangulation::default_tag
>
{
	static
	void
	execute(
		Container &_container,
		Vertex const &_v1,
		Vertex const &_v2,
		Vertex const &_v3
	)
	{
		typename Container::value_type result =
		{{
			_v1,
			_v2,
			_v3
		}};

		_container.insert(
			_container.end(),
			result
		);
	}
};

}
}
}
}

#endif
