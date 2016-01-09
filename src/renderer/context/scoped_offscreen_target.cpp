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


#include <sge/renderer/context/core.hpp>
#include <sge/renderer/context/scoped_offscreen_target.hpp>
#include <sge/renderer/target/offscreen_fwd.hpp>
#include <sge/renderer/target/optional_offscreen_ref.hpp>
#include <fcppt/make_ref.hpp>


sge::renderer::context::scoped_offscreen_target::scoped_offscreen_target(
	sge::renderer::context::core &_context,
	sge::renderer::target::offscreen &_target
)
:
	context_(
		_context
	)
{
	context_.offscreen_target(
		sge::renderer::target::optional_offscreen_ref(
			fcppt::make_ref(
				_target
			)
		)
	);
}

sge::renderer::context::scoped_offscreen_target::~scoped_offscreen_target()
{
	context_.offscreen_target(
		sge::renderer::target::optional_offscreen_ref()
	);
}
