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


#ifndef SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_LEVEL_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_FILL_TEX_COORDINATES_LEVEL_HPP_INCLUDED

#include <sge/sprite/detail/fill_tex_coordinates_impl.hpp>
#include <sge/sprite/object_fwd.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Iterator,
	typename Choices
>
class fill_tex_coordinates_level
{
	FCPPT_NONASSIGNABLE(
		fill_tex_coordinates_level
	);
public:
	typedef sprite::object<
		Choices
	> object;

	fill_tex_coordinates_level(
		Iterator const &_iterator,
		object const &_object
	)
	:
		iterator_(_iterator),
		object_(_object)
	{
	}

	template<
		typename Level
	>
	void
	operator()(
		Level const &
	) const
	{
		if(
			object_. template texture_level<
				Level::value
			>()
		)
			detail::fill_tex_coordinates_impl<
				Level
			>(
				iterator_,
				object_
			);
	}
private:
	Iterator const iterator_;

	object const &object_;
};

}
}
}

#endif
