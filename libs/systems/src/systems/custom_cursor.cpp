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


#include <sge/input/processor_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/cursor_hotspot.hpp>
#include <sge/systems/custom_cursor.hpp>
#include <sge/systems/impl/detail/custom_cursor.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::systems::custom_cursor::custom_cursor(
	sge::input::processor const &_processor,
	sge::renderer::device::ffp &_renderer,
	sge::texture::part const &_texture,
	sge::systems::cursor_hotspot const _hotspot
)
:
	impl_{
		fcppt::make_unique_ptr<
			sge::systems::detail::custom_cursor
		>(
			_processor,
			_renderer,
			_texture,
			_hotspot
		)
	}
{
}

sge::systems::custom_cursor::custom_cursor(
	custom_cursor &&
) = default;

sge::systems::custom_cursor &
sge::systems::custom_cursor::operator=(
	custom_cursor &&
) = default;

sge::systems::custom_cursor::~custom_cursor()
{
}

void
sge::systems::custom_cursor::draw(
	sge::renderer::context::ffp &_context
)
{
	impl_->draw(
		_context
	);
}

sge::systems::cursor_hotspot
sge::systems::custom_cursor::hotspot() const
{
	return
		impl_->hotspot();
}
