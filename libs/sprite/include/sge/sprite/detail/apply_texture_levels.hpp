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


#ifndef SGE_SPRITE_DETAIL_APPLY_TEXTURE_LEVELS_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_APPLY_TEXTURE_LEVELS_HPP_INCLUDED

#include <sge/sprite/config/is_texture_level_count.hpp>
#include <sge/sprite/detail/make_texture_levels.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/for_each.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{

template<
	typename Levels,
	typename Function
>
typename boost::enable_if<
	sge::sprite::config::is_texture_level_count<
		Levels
	>,
	void
>::type
apply_texture_levels(
	Function const &_function
)
{
FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif
	boost::mpl::for_each<
		typename sge::sprite::detail::make_texture_levels<
			Levels
		>::type
	>(
		_function
	);

FCPPT_PP_POP_WARNING
}

}
}
}

#endif
