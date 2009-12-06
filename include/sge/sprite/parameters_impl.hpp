/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SPRITE_PARAMETERS_IMPL_HPP_INCLUDED
#define SGE_SPRITE_PARAMETERS_IMPL_HPP_INCLUDED

#include <sge/sprite/parameters_decl.hpp>

template<
	typename Choices,
	typename Elements
>
sge::sprite::parameters<Choices, Elements>::parameters()
:
	elements_()
{}

template<
	typename Choices,
	typename Elements
>
sge::sprite::parameters<Choices, Elements> const
sge::sprite::parameters<Choices, Elements>::pos(
	typename majutsu::role_return_type<
		flattened_types,
		roles::pos
	>::type const &pos_
) const
{
	return
		this->set<
			roles::pos
		>(
			pos_
		);
}

template<
	typename Choices,
	typename Elements
>
sge::sprite::parameters<Choices, Elements> const
sge::sprite::parameters<Choices, Elements>::texture(
	typename majutsu::role_return_type<
		flattened_types,
		roles::texture
	>::type const &texture_
) const
{
	return
		this->set<
			roles::texture
		>(
			texture_
		);
}

template<
	typename Choices,
	typename Elements
>
sge::sprite::parameters<Choices, Elements> const
sge::sprite::parameters<Choices, Elements>::size(
	typename majutsu::role_return_type<
		flattened_types,
		roles::size
	>::type const &size_
) const
{
	return
		this->set<
			roles::size
		>(
			size_
		);
}

template<
	typename Choices,
	typename Elements
>
sge::sprite::parameters<Choices, Elements> const
sge::sprite::parameters<Choices, Elements>::texture_size() const
{
	return
		this->texture(
			texture_dim<
				Choices
			>()
		);
}

template<
	typename Choices,
	typename Elements
>
sge::sprite::parameters<Choices, Elements> const
sge::sprite::parameters<Choices, Elements>::color(
	typename majutsu::role_return_type<
		flattened_types,
		roles::color
	>::type const &color_
) const
{
	return
		this->set<
			roles::color
		>(
			color_
		);
}

template<
	typename Choices,
	typename Elements
>
template<
	typename Role
>
sge::sprite::parameters<Choices, Elements> const
sge::sprite::parameters<Choices, Elements>::set(
	typename majutsu::role_return_type<
		flattened_types,
		Role
	>::type const &value_
) const
{
	parameters ret(
		*this
	);

	ret.elements_. template set<
		Role
	>(
		value_
	);

	return ret;
}

template<
	typename Choices,
	typename Elements
>
typename sge::sprite::parameters<Choices, Elements>::elements_type const &
sge::sprite::parameters<Choices, Elements>::elements() const
{
	return elements_;
}

#endif
