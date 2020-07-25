//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cursor/hotspot.hpp>
#include <sge/cursor/object.hpp>
#include <sge/cursor/impl/detail/object.hpp>
#include <sge/input/const_processor_ref.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::cursor::object::object(
	sge::input::const_processor_ref const _processor,
	sge::renderer::device::ffp_ref const _renderer,
	sge::texture::const_part_ref const _texture,
	sge::cursor::hotspot _hotspot
)
:
	impl_{
		fcppt::make_unique_ptr<
			sge::cursor::detail::object
		>(
			_processor,
			_renderer,
			_texture,
			std::move(
				_hotspot
			)
		)
	}
{
}

sge::cursor::object::object(
	object &&
)
noexcept
= default;

sge::cursor::object &
sge::cursor::object::operator=(
	object &&
)
noexcept
= default;

sge::cursor::object::~object()
= default;

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
