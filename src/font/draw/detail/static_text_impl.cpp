/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/set_matrices_fwd.hpp>
#include <sge/font/draw/set_states_fwd.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/geometry/update_one.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/src/font/draw/detail/static_text_impl.hpp>
#include <sge/texture/const_optional_part_ref.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/vector/arithmetic.hpp>


sge::font::draw::detail::static_text_impl::static_text_impl(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::text_parameters const &_text_parameters
)
:
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	string_(),
	text_parameters_(
		_text_parameters
	),
	texture_(),
	texture_part_(),
	text_(),
	pos_(
		sge::font::vector::null()
	),
	sprite_buffers_(
		_renderer,
		sge::sprite::buffers::option::static_
	),
	sprite_state_(
		_renderer,
		sge::font::draw::detail::static_text_impl::sprite_state_parameters()
	),
	sprite_(),
	sprite_range_()
{
}

sge::font::draw::detail::static_text_impl::~static_text_impl()
{
}

void
sge::font::draw::detail::static_text_impl::draw(
	sge::renderer::context::ffp &_context,
	sge::font::draw::set_matrices const &_set_matrices,
	sge::font::draw::set_states const &_set_states
)
{
	sge::sprite::render::range_with_options(
		sge::sprite::render::parameters<
			sprite_state_choices
		>(
			_context,
			sprite_buffers_.parameters().vertex_declaration()
		),
		sprite_range_,
		sprite_state_,
		sge::font::draw::detail::static_text_impl::sprite_state_options(
			sge::sprite::state::vertex_options::declaration_and_buffer
		)
		.set<
			sge::sprite::state::roles::transform
		>(
			_set_matrices.get()
		)
		.set<
			sge::sprite::state::roles::rasterizer
		>(
			_set_states.get()
		)
		.set<
			sge::sprite::state::roles::blend
		>(
			_set_states.get()
		)
	);
}

void
sge::font::draw::detail::static_text_impl::string(
	sge::font::string const &_string
)
{
	string_ = _string;
}

void
sge::font::draw::detail::static_text_impl::pos(
	sge::font::vector const &_pos
)
{
	pos_ = _pos;
}

void
sge::font::draw::detail::static_text_impl::color(
	sge::image::color::any::object const &_color
)
{
	sprite_.color(
		sge::image::color::any::convert<
			sge::font::draw::detail::static_text_impl::color_format
		>(
			_color
		)
	);
}

sge::font::string const
sge::font::draw::detail::static_text_impl::string() const
{
	return string_;
}

sge::font::vector const
sge::font::draw::detail::static_text_impl::pos() const
{
	return pos_;
}

sge::font::rect const
sge::font::draw::detail::static_text_impl::rect() const
{
	return text_->rect();
}

void
sge::font::draw::detail::static_text_impl::rebuild_texture()
{
	text_.take(
		font_.create_text(
			string_,
			text_parameters_
		)
	);

	sge::renderer::dim2 const new_size(
		fcppt::math::dim::structure_cast<
			sge::renderer::dim2
		>(
			text_->rect().size()
		)
	);

	if(
		!texture_
		||
		texture_->size()
		!=
		new_size
	)
	{
		sge::image::color::optional_format const font_color_format(
			font_.color_format()
		);

		texture_.take(
			renderer_.create_planar_texture(
				sge::renderer::texture::planar_parameters(
					new_size,
					font_color_format
					?
						*font_color_format
					:
						sge::image::color::format::a8,
					sge::renderer::texture::mipmap::off(),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::capabilities_field::null()
				)
			)
		);

		texture_part_.take(
			fcppt::make_unique_ptr<
				sge::texture::part_raw_ref
			>(
				fcppt::ref(
					*texture_
				)
			)
		);
	}

	{
		sge::renderer::texture::scoped_planar_lock const lock(
			*texture_,
			sge::renderer::lock_mode::writeonly
		);

		text_->render(
			lock.value()
		);
	}

	this->rebuild_sprite();
}

void
sge::font::draw::detail::static_text_impl::rebuild_sprite()
{
	sprite_.texture(
		sge::texture::const_optional_part_ref(
			*texture_part_
		)
	);

	sprite_.pos(
		pos_
		+
		text_->rect().pos()
	);

	sprite_.size(
		text_->rect().size()
	);

	sprite_range_ =
		sge::sprite::geometry::update_one(
			sprite_,
			sprite_buffers_
		);

}
