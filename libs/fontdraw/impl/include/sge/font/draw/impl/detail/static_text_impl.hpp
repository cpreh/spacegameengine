//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_FONT_DRAW_IMPL_DETAIL_STATIC_TEXT_IMPL_HPP_INCLUDED
#define SGE_FONT_DRAW_IMPL_DETAIL_STATIC_TEXT_IMPL_HPP_INCLUDED

#include <sge/font/dim_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/rect_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/text_unique_ptr.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/vector_fwd.hpp>
#include <sge/font/draw/set_matrices_fwd.hpp>
#include <sge/font/draw/set_states_fwd.hpp>
#include <sge/font/draw/detail/static_text_impl_fwd.hpp>
#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/state/ffp/sampler/optional_object_unique_ptr.hpp>
#include <sge/renderer/texture/emulate_srgb_fwd.hpp>
#include <sge/sprite/object_decl.hpp>
#include <sge/sprite/buffers/single_decl.hpp>
#include <sge/sprite/buffers/with_declaration_decl.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/pos.hpp>
#include <sge/sprite/config/pos_option.hpp>
#include <sge/sprite/config/texture_coordinates.hpp>
#include <sge/sprite/config/texture_level_count.hpp>
#include <sge/sprite/config/texture_ownership.hpp>
#include <sge/sprite/config/texture_size_option.hpp>
#include <sge/sprite/config/type_choices.hpp>
#include <sge/sprite/config/unit_type.hpp>
#include <sge/sprite/config/with_color.hpp>
#include <sge/sprite/config/with_texture.hpp>
#include <sge/sprite/render/range_decl.hpp>
#include <sge/sprite/state/all_choices.hpp>
#include <sge/sprite/state/object_decl.hpp>
#include <sge/sprite/state/options_fwd.hpp>
#include <sge/sprite/state/parameters_fwd.hpp>
#include <sge/sprite/types/vector_fwd.hpp>
#include <sge/texture/part_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <brigand/sequences/list.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace font
{
namespace draw
{
namespace detail
{

class static_text_impl
{
	FCPPT_NONCOPYABLE(
		static_text_impl
	);
public:
	static_text_impl(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::font::string const &,
		sge::font::text_parameters const &,
		sge::font::vector const &,
		sge::image::color::any::object const &,
		sge::renderer::texture::emulate_srgb
	);

	~static_text_impl();

	void
	draw(
		sge::renderer::context::ffp &,
		sge::font::draw::set_matrices const &,
		sge::font::draw::set_states const &
	);

	void
	pos(
		sge::font::vector const &
	);

	void
	color(
		sge::image::color::any::object const &
	);

	sge::font::vector
	pos() const;

	sge::font::rect
	rect() const;

	sge::font::dim
	logical_size() const;

	sge::font::text const &
	text() const;
private:
	void
	rebuild_sprite_range();

	sge::renderer::state::ffp::sampler::optional_object_unique_ptr const sampler_state_;

	sge::font::text_unique_ptr const text_;

	sge::texture::part_unique_ptr const texture_part_;

	typedef
	sge::image::color::rgba8_format
	color_format;

	typedef
	sge::sprite::config::choices<
		sge::sprite::config::type_choices<
			sge::sprite::config::unit_type<
				sge::font::unit
			>,
			sge::sprite::config::float_type<
				float
			>
		>,
		sge::sprite::config::pos<
			sge::sprite::config::pos_option::pos
		>,
		sge::sprite::config::normal_size<
			sge::sprite::config::texture_size_option::always
		>,
		brigand::list<
			sge::sprite::config::with_color<
				sge::font::draw::detail::static_text_impl::color_format
			>,
			sge::sprite::config::with_texture<
				sge::sprite::config::texture_level_count<
					1u
				>,
				sge::sprite::config::texture_coordinates::automatic,
				sge::sprite::config::texture_ownership::reference
			>
		>
	>
	sprite_choices;

	typedef
	sge::sprite::object<
		sprite_choices
	>
	sprite_object;

	typedef
	sge::sprite::buffers::with_declaration<
		sge::sprite::buffers::single<
			sprite_choices
		>
	>
	sprite_buffers;

	typedef
	sge::sprite::state::all_choices
	sprite_state_choices;

	typedef
	sge::sprite::state::object<
		sprite_state_choices
	>
	sprite_state;

	typedef
	sge::sprite::state::parameters<
		sprite_state_choices
	>
	sprite_state_parameters;

	typedef
	sge::sprite::state::options<
		sprite_state_choices
	>
	sprite_state_options;

	typedef
	sge::sprite::render::range<
		sprite_choices
	>
	sprite_range;

	sge::font::draw::detail::static_text_impl::sprite_range
	make_sprite_range();

	typedef
	sge::sprite::types::vector<
		sprite_choices::type_choices
	>
	sprite_pos_type;

	sge::font::draw::detail::static_text_impl::sprite_pos_type
	sprite_pos(
		sge::font::vector const &
	) const;

	sprite_buffers sprite_buffers_;

	sprite_state sprite_state_;

	sprite_object sprite_;

	sprite_range sprite_range_;
};

}
}
}
}

#endif
