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


#ifndef SGE_SPRITE_CONFIG_NORMAL_SIZE_HPP_INCLUDED
#define SGE_SPRITE_CONFIG_NORMAL_SIZE_HPP_INCLUDED

#include <sge/sprite/config/normal_size_fwd.hpp>
#include <sge/sprite/config/size_choice.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/detail/primitives/normal_size.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace config
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	sge::sprite::config::texture_size_option TextureSize
>
struct normal_size final
:
	sge::sprite::config::size_choice
{
	typedef
	std::integral_constant<
		sge::sprite::config::texture_size_option,
		TextureSize
	>
	texture_option;

	template<
		typename Choices
	>
	struct apply
	:
	sge::sprite::detail::primitives::normal_size<
		Choices,
		TextureSize
	>
	{
	};
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
