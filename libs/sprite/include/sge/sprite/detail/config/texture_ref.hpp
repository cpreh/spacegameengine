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


#ifndef SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_TEXTURE_REF_HPP_INCLUDED

#include <sge/sprite/detail/config/find_texture_config.hpp>
#include <sge/sprite/detail/config/lazy_head.hpp>
#include <sge/sprite/detail/primitives/texture_ref_type.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/functions/eval_if.hpp>
#include <brigand/functions/arithmetic/identity.hpp>
#include <brigand/sequences/list.hpp>
#include <brigand/types/no_such_type.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

template<
	typename Choices
>
struct texture_ref
{
private:
	template<
		typename Element
	>
	using
	obtain_ref_type
	=
	typename
	sge::sprite::detail::primitives::texture_ref_type<
		Element::ownership::value
	>::type;

	typedef
	typename
	sge::sprite::detail::config::find_texture_config<
		Choices
	>::type
	texture_list;
public:
	typedef
	typename
	brigand::eval_if<
		std::is_same<
			texture_list,
			brigand::list<>
		>,
		brigand::identity<
			brigand::no_such_type_
		>,
		sge::sprite::detail::config::lazy_head<
			obtain_ref_type,
			texture_list
		>
	>::type
	type;
};

}
}
}
}

#endif
