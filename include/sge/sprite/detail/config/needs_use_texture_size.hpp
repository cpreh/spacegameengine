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


#ifndef SGE_SPRITE_DETAIL_CONFIG_NEEDS_USE_TEXTURE_SIZE_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_CONFIG_NEEDS_USE_TEXTURE_SIZE_HPP_INCLUDED

#include <sge/sprite/detail/config/has_normal_size.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace config
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Choices
>
struct needs_use_texture_size
:
boost::mpl::and_<
	sge::sprite::detail::config::has_normal_size<
		Choices
	>,
	sge::sprite::detail::config::has_texture<
		Choices
	>
>
{
};

FCPPT_PP_POP_WARNING

}
}
}
}

#endif
