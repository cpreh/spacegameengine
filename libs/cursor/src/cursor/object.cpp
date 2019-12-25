//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cursor/hotspot.hpp>
#include <sge/cursor/object.hpp>
#include <sge/cursor/impl/detail/object.hpp>
#include <sge/input/processor_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/texture/part_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::cursor::object::object(
	sge::input::processor const &_processor,
	sge::renderer::device::ffp &_renderer,
	sge::texture::part const &_texture,
	sge::cursor::hotspot const _hotspot
)
:
	impl_{
		fcppt::make_unique_ptr<
			sge::cursor::detail::object
		>(
			_processor,
			_renderer,
			_texture,
			_hotspot
		)
	}
{
}

sge::cursor::object::object(
	object &&
) = default;

sge::cursor::object &
sge::cursor::object::operator=(
	object &&
) = default;

sge::cursor::object::~object()
{
}

void
sge::cursor::object::draw(
	sge::renderer::context::ffp &_context
)
{
	this->impl_->draw(
		_context
	);
}

sge::cursor::hotspot
sge::cursor::object::hotspot() const
{
	return
		this->impl_->hotspot();
}
