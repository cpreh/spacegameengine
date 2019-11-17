//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/rgba8_format.hpp>
#include <sge/image/pixel/mizuiro_type.hpp>
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
#include <sge/sprite/roles/color.hpp>
#include <sge/sprite/roles/pos.hpp>
#include <sge/sprite/roles/size.hpp>
#include <sge/sprite/roles/texture0.hpp>
#include <sge/sprite/types/dim.hpp>
#include <sge/sprite/types/vector.hpp>
#include <sge/sprite/detail/make_class.hpp>
#include <sge/texture/const_part_shared_ptr.hpp>
#include <fcppt/metal/maps_equal.hpp>
#include <fcppt/record/element_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal/list/list.hpp>
#include <metal/map/map.hpp>
#include <metal/pair/pair.hpp>
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

typedef
fcppt::record::element_map<
	sge::sprite::detail::make_class<
		simple_sprite_choices
	>
>
simple_sprite_elements;

static_assert(
	fcppt::metal::maps_equal<
		simple_sprite_elements,
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

typedef
fcppt::record::element_map<
	sge::sprite::detail::make_class<
		color_sprite_choices
	>
>
color_sprite_elements;

static_assert(
	fcppt::metal::maps_equal<
		color_sprite_elements,
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

typedef
fcppt::record::element_map<
	sge::sprite::detail::make_class<
		texture_sprite_choices
	>
>
texture_sprite_elements;

static_assert(
	fcppt::metal::maps_equal<
		texture_sprite_elements,
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

}

int
main()
{
}
