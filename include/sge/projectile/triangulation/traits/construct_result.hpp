/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_PROJECTILE_TRIANGULATION_TRAITS_CONSTRUCT_RESULT_HPP_INCLUDED
#define SGE_PROJECTILE_TRIANGULATION_TRAITS_CONSTRUCT_RESULT_HPP_INCLUDED

#include <sge/projectile/triangulation/default_tag.hpp>

namespace sge
{
namespace projectile
{
namespace triangulation
{
namespace traits
{

template<
	typename Result,
	typename Vertex,
	typename Tag
>
struct construct_result;

template<
	typename Result,
	typename Vertex
>
struct construct_result<
	Result,
	Vertex,
	triangulation::default_tag
>
{
	static
	Result const
	execute(
		Vertex const &_v1,
		Vertex const &_v2,
		Vertex const &_v3
	)
	{
		Result const ret = {{
			_v1,
			_v2,
			_v3
		}};

		return ret;
	}
};

}
}
}
}

#endif
