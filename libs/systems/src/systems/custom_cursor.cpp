//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
