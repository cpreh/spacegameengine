//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/font/dim.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/color_format.hpp>
#include <sge/font/draw/create_ffp_sampler.hpp>
#include <sge/font/draw/create_texture.hpp>
#include <sge/font/draw/set_matrices_fwd.hpp>
#include <sge/font/draw/set_states_fwd.hpp>
#include <sge/font/draw/impl/detail/static_text_impl.hpp>
#include <sge/image/color/optional_format.hpp>
#include <sge/image/color/any/convert.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref.hpp>
#include <sge/renderer/state/ffp/sampler/const_object_ref_vector.hpp>
#include <sge/renderer/state/ffp/sampler/object.hpp>
#include <sge/renderer/state/ffp/sampler/object_unique_ptr.hpp>
#include <sge/renderer/state/ffp/sampler/scoped.hpp>
#include <sge/renderer/state/ffp/sampler/scoped_unique_ptr.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/buffers/single_impl.hpp>
#include <sge/sprite/buffers/with_declaration_impl.hpp>
#include <sge/sprite/geometry/update_one.hpp>
#include <sge/sprite/render/parameters.hpp>
#include <sge/sprite/render/range_impl.hpp>
#include <sge/sprite/render/range_with_options.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/state/object_impl.hpp>
#include <sge/sprite/state/options_impl.hpp>
#include <sge/sprite/state/parameters_impl.hpp>
#include <sge/sprite/state/vertex_options.hpp>
#include <sge/sprite/state/roles/blend.hpp>
#include <sge/sprite/state/roles/rasterizer.hpp>
#include <sge/sprite/state/roles/transform.hpp>
#include <sge/sprite/types/vector.hpp>
#include <sge/texture/const_part_ref.hpp>
#include <sge/texture/part.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sge::font::draw::detail::static_text_impl::static_text_impl(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_string,
	sge::font::text_parameters const &_text_parameters,
	sge::font::vector const &_pos,
	sge::image::color::any::object const &_color,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
:
	sampler_state_(
		sge::font::draw::create_ffp_sampler(
			_renderer,
			sge::font::draw::color_format(
				_font.preferred_color_format()
			)
		)
	),
	text_(
		_font.create_text(
			_string,
			_text_parameters
		)
	),
	texture_part_(
		sge::font::draw::create_texture(
			_renderer,
			*text_,
			sge::font::draw::color_format(
				_font.preferred_color_format()
			),
			_emulate_srgb
		)
	),
	sprite_buffers_(
		_renderer,
		sge::sprite::buffers::option::static_
	),
	sprite_state_(
		_renderer,
		sge::font::draw::detail::static_text_impl::sprite_state_parameters()
	),
	sprite_(
		sge::sprite::roles::pos{} =
			this->sprite_pos(
				_pos
			),
		sge::sprite::roles::color{} =
			sge::image::color::any::convert<
				sge::font::draw::detail::static_text_impl::color_format
			>(
				_color
			),
		sge::sprite::roles::texture0{} =
			sge::texture::const_part_ref(
				*texture_part_
			)
	),
	sprite_range_(
		this->make_sprite_range()
	)
{
}

FCPPT_PP_POP_WARNING


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
	typedef
	fcppt::optional::object<
		sge::renderer::state::ffp::sampler::scoped_unique_ptr
	>
	optional_scoped_sampler;

	optional_scoped_sampler const scoped_state(
		fcppt::optional::map(
			sampler_state_,
			[
				&_context
			](
				sge::renderer::state::ffp::sampler::object_unique_ptr const &_sampler_state
			)
			{
				return
					fcppt::make_unique_ptr<
						sge::renderer::state::ffp::sampler::scoped
					>(
						fcppt::make_ref(
							_context
						),
						sge::renderer::state::ffp::sampler::const_object_ref_vector{
							sge::renderer::state::ffp::sampler::const_object_ref(
								*_sampler_state
							)
						}
					);
			}
		)
	);

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
sge::font::draw::detail::static_text_impl::pos(
	sge::font::vector const &_pos
)
{
	sprite_.pos(
		this->sprite_pos(
			_pos
		)
	);

	this->rebuild_sprite_range();
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

	this->rebuild_sprite_range();
}

sge::font::vector
sge::font::draw::detail::static_text_impl::pos() const
{
	return
		sprite_.pos()
		-
		text_->rect().pos();
}

sge::font::rect
sge::font::draw::detail::static_text_impl::rect() const
{
	return
		text_->rect();
}

sge::font::dim
sge::font::draw::detail::static_text_impl::logical_size() const
{
	return
		text_->logical_size();
}

sge::font::text const &
sge::font::draw::detail::static_text_impl::text() const
{
	return
		*text_;
}

void
sge::font::draw::detail::static_text_impl::rebuild_sprite_range()
{
	sprite_range_ =
		this->make_sprite_range();
}

sge::font::draw::detail::static_text_impl::sprite_range
sge::font::draw::detail::static_text_impl::make_sprite_range()
{
	return
		sge::sprite::geometry::update_one(
			sprite_,
			sprite_buffers_
		);
}

sge::font::draw::detail::static_text_impl::sprite_pos_type
sge::font::draw::detail::static_text_impl::sprite_pos(
	sge::font::vector const &_pos
) const
{
	return
		_pos
		+
		text_->rect().pos();
}
