//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/draw/set_matrices.hpp>
#include <sge/font/draw/set_states.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/gui/impl/draw_image.hpp>
#include <sge/gui/impl/draw_image_repeat.hpp>
#include <sge/gui/impl/fill_rect.hpp>
#include <sge/gui/impl/renderer/stateless.hpp>
#include <sge/gui/renderer/base.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/texture/part_fwd.hpp>


sge::gui::impl::renderer::stateless::stateless(
	sge::renderer::device::core_ref const _renderer
)
:
	sge::gui::renderer::base(),
	renderer_(
		_renderer
	)
{
}

sge::gui::impl::renderer::stateless::~stateless()
= default;

void
sge::gui::impl::renderer::stateless::fill_rect(
	sge::renderer::context::ffp &_context,
	sge::rucksack::rect const &_rect,
	sge::image::color::any::object const &_color
)
{
	sge::gui::impl::fill_rect(
		renderer_.get(),
		_context,
		_rect,
		_color
	);
}

void
sge::gui::impl::renderer::stateless::draw_image(
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::vector const &_pos
)
{
	sge::gui::impl::draw_image(
		renderer_.get(),
		_context,
		_texture,
		_pos
	);
}

void
sge::gui::impl::renderer::stateless::draw_image_repeat(
	sge::renderer::context::ffp &_context,
	sge::texture::part const &_texture,
	sge::rucksack::rect const &_area
)
{
	sge::gui::impl::draw_image_repeat(
		renderer_.get(),
		_context,
		_texture,
		_area
	);
}

void
sge::gui::impl::renderer::stateless::draw_static_text(
	sge::renderer::context::ffp &_context,
	sge::font::draw::static_text const &_static_text
)
{
	_static_text.draw_advanced(
		_context,
		sge::font::draw::set_matrices(
			false
		),
		sge::font::draw::set_states(
			false
		)
	);
}
