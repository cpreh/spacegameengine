/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SPRITE_COMPARE_DEFAULT_HPP_INCLUDED
#define SGE_SPRITE_COMPARE_DEFAULT_HPP_INCLUDED

#include <sge/sprite/object_fwd.hpp>
#include <sge/sprite/compare/nothing.hpp>
#include <sge/sprite/compare/textures.hpp>
#include <sge/sprite/detail/config/has_texture.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/not.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace compare
{

struct default_
{
	typedef bool result_type;

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

	template<
		typename Choices
	>
	struct is_trivial
	:
	boost::mpl::not_<
		typename sge::sprite::detail::config::has_texture<
			Choices
		>::type
	>
	{
	};

FCPPT_PP_POP_WARNING

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
		return
			sge::sprite::compare::textures()(
				_left,
				_right
			);
	}

	template<
		typename Choices
	>
	typename boost::disable_if<
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
		return
			sge::sprite::compare::nothing()(
				_left,
				_right
			);
	}
};

}
}
}

#endif
