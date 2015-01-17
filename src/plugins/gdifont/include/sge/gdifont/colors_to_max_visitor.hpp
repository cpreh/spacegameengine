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


#ifndef SGE_GDIFONT_COLORS_TO_MAX_VISITOR_HPP_INCLUDED
#define SGE_GDIFONT_COLORS_TO_MAX_VISITOR_HPP_INCLUDED

#include <sge/gdifont/a8_view.hpp>
#include <sge/gdifont/alpha_to_max.hpp>
#include <mizuiro/image/algorithm/for_each.hpp>
#include <fcppt/assert/unreachable.hpp>


namespace sge
{
namespace gdifont
{

struct colors_to_max_visitor
{
	typedef void result_type;

	template<
		typename View
	>
	result_type
	operator()(
		View const &
	) const
	{
		// TOOD: Maybe we have to support a generic version here
		FCPPT_ASSERT_UNREACHABLE;
	}

	result_type
	operator()(
		sge::gdifont::a8_view const &_view
	) const
	{
		mizuiro::image::algorithm::for_each(
			_view,
			sge::gdifont::alpha_to_max()
		);
	}
};

}
}

#endif
