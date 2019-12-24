//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/index.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/part_from_list.hpp>
#include <sge/sprite/vertex_format.hpp>
#include <sge/sprite/config/choices.hpp>
#include <sge/sprite/config/custom_texture_point_pos.hpp>
#include <sge/sprite/config/float_type.hpp>
#include <sge/sprite/config/normal_size.hpp>
#include <sge/sprite/config/no_texture_point_size.hpp>
#include <sge/sprite/config/point_size.hpp>
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
#include <sge/sprite/config/with_texture_point_size.hpp>
#include <sge/sprite/detail/vf/color.hpp>
#include <sge/sprite/detail/vf/point_size.hpp>
#include <sge/sprite/detail/vf/pos.hpp>
#include <sge/sprite/detail/vf/texpos.hpp>
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/point_size.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/sprite/types/point_size.hpp>
#include <sge/sprite/types/vector.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/metal/maps_equal.hpp>
#include <fcppt/record/element_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

typedef
sge::sprite::config::type_choices<
	sge::sprite::config::unit_type<
		int
	>,
	sge::sprite::config::float_type<
		float
	>
>
type_choices;

typedef
sge::sprite::config::choices<
	type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::never
	>,
	metal::list<>
>
simple_sprite_choices;

static_assert(
	fcppt::metal::maps_equal<
		fcppt::record::element_map<
			sge::sprite::detail::make_class<
				simple_sprite_choices
			>
		>,
		metal::map<
			metal::pair<
				sge::sprite::roles::pos,
				sge::sprite::types::vector<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::size,
				sge::sprite::types::dim<
					type_choices
				>
			>
		>
	>::value
);

static_assert(
	std::is_same_v<
		sge::sprite::vertex_format<
			simple_sprite_choices
		>,
		sge::renderer::vf::format<
			sge::renderer::vf::part<
				sge::sprite::detail::vf::pos<
					simple_sprite_choices
				>
			>
		>
	>
);

typedef
sge::image::color::rgba8_format
color_format;

typedef
sge::sprite::config::choices<
	type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::never
	>,
	metal::list<
		sge::sprite::config::with_color<
			color_format
		>
	>
>
color_sprite_choices;

static_assert(
	fcppt::metal::maps_equal<
		fcppt::record::element_map<
			sge::sprite::detail::make_class<
				color_sprite_choices
			>
		>,
		metal::map<
			metal::pair<
				sge::sprite::roles::pos,
				sge::sprite::types::vector<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::size,
				sge::sprite::types::dim<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::color,
				sge::image::pixel::mizuiro_type<
					color_format
				>
			>
		>
	>::value
);

static_assert(
	std::is_same_v<
		sge::sprite::vertex_format<
			color_sprite_choices
		>,
		sge::renderer::vf::format<
			sge::renderer::vf::part<
				sge::sprite::detail::vf::pos<
					color_sprite_choices
				>,
				sge::sprite::detail::vf::color<
					color_sprite_choices
				>
			>
		>
	>
);

typedef
sge::sprite::config::choices<
	type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::normal_size<
		sge::sprite::config::texture_size_option::never
	>,
	metal::list<
		sge::sprite::config::with_texture<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::texture_coordinates::automatic,
			sge::sprite::config::texture_ownership::shared
		>
	>
>
texture_sprite_choices;

static_assert(
	fcppt::metal::maps_equal<
		fcppt::record::element_map<
			sge::sprite::detail::make_class<
				texture_sprite_choices
			>
		>,
		metal::map<
			metal::pair<
				sge::sprite::roles::pos,
				sge::sprite::types::vector<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::size,
				sge::sprite::types::dim<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::texture0,
				sge::texture::const_part_shared_ptr
			>
		>
	>::value
);

static_assert(
	std::is_same_v<
		sge::sprite::vertex_format<
			texture_sprite_choices
		>,
		sge::renderer::vf::format<
			sge::renderer::vf::part_from_list<
				metal::join<
					metal::list<
						sge::sprite::detail::vf::pos<
							texture_sprite_choices
						>
					>,
					sge::sprite::detail::vf::texpos<
						texture_sprite_choices
					>
				>
			>
		>
	>
);

typedef
sge::sprite::config::choices<
	type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::point_size<
		sge::renderer::vf::index<
			0u
		>
	>,
	metal::list<>
>
point_sprite_choices;

static_assert(
	fcppt::metal::maps_equal<
		fcppt::record::element_map<
			sge::sprite::detail::make_class<
				point_sprite_choices
			>
		>,
		metal::map<
			metal::pair<
				sge::sprite::roles::pos,
				sge::sprite::types::vector<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::point_size,
				sge::sprite::types::point_size<
					type_choices
				>
			>
		>
	>::value
);

static_assert(
	std::is_same_v<
		sge::sprite::vertex_format<
			point_sprite_choices
		>,
		sge::renderer::vf::format<
			sge::renderer::vf::part<
				sge::sprite::detail::vf::pos<
					point_sprite_choices
				>,
				sge::sprite::detail::vf::point_size<
					point_sprite_choices
				>
			>
		>
	>
);

typedef
sge::sprite::config::choices<
	type_choices,
	sge::sprite::config::pos<
		sge::sprite::config::pos_option::pos
	>,
	sge::sprite::config::point_size<
		sge::renderer::vf::index<
			0u
		>
	>,
	metal::list<
		sge::sprite::config::with_texture_point_size<
			sge::sprite::config::texture_level_count<
				1u
			>,
			sge::sprite::config::custom_texture_point_pos<
				false
			>,
			sge::sprite::config::no_texture_point_size,
			sge::sprite::config::texture_ownership::shared
		>
	>
>
texture_point_sprite_choices;

static_assert(
	fcppt::metal::maps_equal<
		fcppt::record::element_map<
			sge::sprite::detail::make_class<
				texture_point_sprite_choices
			>
		>,
		metal::map<
			metal::pair<
				sge::sprite::roles::pos,
				sge::sprite::types::vector<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::point_size,
				sge::sprite::types::point_size<
					type_choices
				>
			>,
			metal::pair<
				sge::sprite::roles::texture0,
				sge::texture::const_part_shared_ptr
			>
		>
	>::value
);

static_assert(
	std::is_same_v<
		sge::sprite::vertex_format<
			texture_point_sprite_choices
		>,
		sge::renderer::vf::format<
			sge::renderer::vf::part<
				sge::sprite::detail::vf::pos<
					point_sprite_choices
				>,
				sge::sprite::detail::vf::point_size<
					point_sprite_choices
				>
			>
		>
	>
);

}

int
main()
{
}
