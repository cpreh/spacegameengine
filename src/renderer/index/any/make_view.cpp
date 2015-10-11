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


#include <sge/renderer/index/format_16.hpp>
#include <sge/renderer/index/format_32.hpp>
#include <sge/renderer/index/view.hpp>
#include <sge/renderer/index/any/make_view.hpp>
#include <sge/renderer/index/any/view.hpp>
#include <sge/renderer/index/dynamic/format.hpp>
#include <sge/renderer/index/dynamic/view.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::index::any::view
sge::renderer::index::any::make_view(
	sge::renderer::index::dynamic::view const &_view
)
{
	// TODO: Simplify this
	switch(
		_view.format()
	)
	{
	case sge::renderer::index::dynamic::format::i16:
		return
			sge::renderer::index::any::view{
				sge::renderer::index::view<
					sge::renderer::index::format_16
				>(
					_view.data(),
					_view.size()
				)
			};
	case sge::renderer::index::dynamic::format::i32:
		return
			sge::renderer::index::any::view{
				sge::renderer::index::view<
					sge::renderer::index::format_32
				>(
					_view.data(),
					_view.size()
				)
			};
	}

	FCPPT_ASSERT_UNREACHABLE;
}
