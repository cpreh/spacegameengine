/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_PRIMITIVES_TEXTURE_POINT_SIZE_HPP_INCLUDED

#include <sge/sprite/config/custom_texture_point_size_fwd.hpp>
#include <sge/sprite/config/no_texture_point_size_fwd.hpp>
#include <sge/sprite/detail/transform_texture_levels_static.hpp>
#include <sge/sprite/roles/texture_point_size.hpp>
#include <sge/sprite/types/texture_point_size.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/lambda/bind.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/sequences/size.hpp>
#include <brigand/types/args.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace primitives
{

template<
	typename Choices,
	typename Levels,
	typename PointSize
>
struct texture_point_size;

template<
	typename Choices,
	typename Levels
>
struct texture_point_size<
	Choices,
	Levels,
	sge::sprite::config::no_texture_point_size
>
{
	typedef
	brigand::list<>
	type;
};

template<
	typename Choices,
	typename Levels,
	typename AttributeNames
>
struct texture_point_size<
	Choices,
	Levels,
	sge::sprite::config::custom_texture_point_size<
		AttributeNames
	>
>
{
private:
	template<
		typename Level
	>
	using
	make_role
	=
	fcppt::record::element<
		sge::sprite::roles::texture_point_size<
			Level::value
		>,
		sge::sprite::types::texture_point_size<
			typename
			Choices::type_choices
		>
	>;

	static_assert(
		brigand::size<
			AttributeNames
		>::value
		==
		Levels,
		"The number of attribute names must match the number of texture levels"
	);
public:
	typedef
	sge::sprite::detail::transform_texture_levels_static<
		brigand::bind<
			make_role,
			brigand::_1
		>,
		Levels
	>
	type;
};

}
}
}
}

#endif
