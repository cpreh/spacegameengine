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


#ifndef SGE_SPRITE_DEFAULT_COMPARE_HPP_INCLUDED
#define SGE_SPRITE_DEFAULT_COMPARE_HPP_INCLUDED

#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{

struct default_compare
{
	typedef bool result_type;

	typedef boost::mpl::false_ is_trivial;

	template<
		typename Choices
	>
	typename boost::enable_if<
		sge::sprite::detail::config::has_texture<
			Choices
		>,
		result_type
	>::type
	operator()(
		sge::sprite::object<
			Choices
		> const &_left,
		sge::sprite::object<
			Choices
		> const &_right
	) const
	{
		// FIXME: compare all texture levels!
		return
			!_left.texture()
			||
			!_right.texture()
			?
				_left.texture()
				< _right.texture()
			:
				_left.texture()->texture()
				<
				_right.texture()->texture()
			;
	}
};

}
}

#endif
