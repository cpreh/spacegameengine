//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/convert.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/raw_value.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/iterator.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/proxy.hpp>
#include <sge/renderer/vf/set_proxy.hpp>
#include <sge/renderer/vf/vertex.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/renderer/vf/view.hpp>
#include <sge/renderer/vf/dynamic/any.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/element.hpp>
#include <sge/renderer/vf/dynamic/element_count.hpp>
#include <sge/renderer/vf/dynamic/element_type.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/make_format.hpp>
#include <sge/renderer/vf/dynamic/offset.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <sge/renderer/vf/dynamic/view.hpp>
#include <sge/renderer/vf/labels/color.hpp>
#include <sge/renderer/vf/labels/pos.hpp>
#include <mizuiro/color/object_fwd.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/math/vector/output.hpp>
#include <fcppt/math/vector/static.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/record/are_equivalent.hpp>
#include <fcppt/record/element.hpp>
#include <fcppt/record/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <catch2/catch.hpp>
#include <array>
#include <cstddef>
#include <cstring>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


// TODO(philipp)
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wfloat-equal)
#include <fcppt/math/vector/comparison.hpp>
FCPPT_PP_POP_WARNING


namespace
{

template<
	sge::renderer::vf::vertex_size Size
>
using
static_size
=
std::integral_constant<
	sge::renderer::vf::vertex_size,
	Size
>;

}

TEST_CASE(
	"renderer/vf/pos color interleaved",
	"[sge]"
)
{
	using
	pos3_type
	=
	sge::renderer::vf::pos<
		float,
		3
	>;

	using
	color_format
	=
	sge::image::color::bgra8_format;

	using
	color_type
	=
	sge::renderer::vf::color<
		color_format
	>;

	using
	format_part
	=
	sge::renderer::vf::part<
		pos3_type,
		color_type
	>;

	static_assert(
		std::is_same_v<
			format_part::offsets,
			metal::list<
				static_size<
					0
				>,
				static_size<
					3 * sizeof(float)
				>,
				static_size<
					3 * sizeof(float)
					+ 4
				>
			>
		>
	);

	static_assert(
		fcppt::record::are_equivalent<
			sge::renderer::vf::vertex<
				format_part
			>::record_type,
			fcppt::record::object<
				fcppt::record::element<
					sge::renderer::vf::labels::pos,
					fcppt::math::vector::static_<
						float,
						3
					>
				>,
				fcppt::record::element<
					sge::renderer::vf::labels::color,
					mizuiro::color::object<
						color_format
					>
				>
			>
		>::value
	);

	using
	format
	=
	sge::renderer::vf::format<
		format_part
	>;

	sge::renderer::vf::dynamic::format const dynamic_format{
		sge::renderer::vf::dynamic::make_format<
			format
		>()
	};

	sge::renderer::vf::dynamic::stride const stride{
		3 * sizeof(float)
		+ 4
	};

	CHECK(
		dynamic_format.parts()
		==
		sge::renderer::vf::dynamic::part_list{
			sge::renderer::vf::dynamic::part{
				sge::renderer::vf::dynamic::ordered_element_list{
					sge::renderer::vf::dynamic::ordered_element{
						sge::renderer::vf::dynamic::element{
							sge::renderer::vf::dynamic::any{
								sge::renderer::vf::dynamic::pos{
									sge::renderer::vf::dynamic::vector{
										sge::renderer::vf::dynamic::element_type::float_,
										sge::renderer::vf::dynamic::element_count{3U}
									}
								}
							}
						},
						sge::renderer::vf::dynamic::offset{0U}
					},
					sge::renderer::vf::dynamic::ordered_element{
						sge::renderer::vf::dynamic::element{
							sge::renderer::vf::dynamic::any{
								sge::renderer::vf::dynamic::color{
									sge::image::color::format::bgra8
								}
							}
						},
						sge::renderer::vf::dynamic::offset{
							3 * sizeof(float)
						}
					}
				},
				stride
			}
		}
	);

	using
	view_type
	=
	sge::renderer::vf::view<
		format_part
	>;

	std::array<
		sge::renderer::raw_value,
		3 * format_part::stride::value
	> test_data{};

	using
	vec3
	=
	pos3_type::packed_type;

	using
	vertex
	=
	sge::renderer::vf::vertex<
		format_part
	>;

	{
		sge::renderer::vf::dynamic::view const dynamic_view{
			test_data.data(),
			sge::renderer::vertex::count{3U},
			fcppt::make_cref(
				dynamic_format.parts().at(0)
			),
			sge::renderer::vf::dynamic::part_index{0U}
		};

		view_type const view{
			dynamic_view
		};

		view_type::iterator it{
			view.begin()
		};

		// Assignment of individual values
		(*it).set<
			sge::renderer::vf::labels::pos
		>(
			vec3(-1.F, 1.F, 0.F)
		);

		(*it).set<
			sge::renderer::vf::labels::color
		>(
			sge::image::color::convert<
				color_format
			>(
				sge::image::color::predef::cyan()
			)
		);

		++it;

		// Assignment of a whole vertex
		*it =
			vertex{
				sge::renderer::vf::labels::pos{} =
					vec3(-1.F, -1.F, 0.F),
				sge::renderer::vf::labels::color{} =
					sge::image::color::convert<
						color_format
					>(
						sge::image::color::predef::yellow()
					)
			};

		++it;

		// Assignment using the free function
		sge::renderer::vf::set_proxy(
			*it,
			sge::renderer::vf::labels::pos{},
			vec3(1.F, 1.F, 0.F)
		);

		sge::renderer::vf::set_proxy(
			*it,
			sge::renderer::vf::labels::color{},
			sge::image::color::convert<
				color_format
			>(
				sge::image::color::predef::magenta()
			)
		);
	}

	// TODO(philipp): Test get

	auto const vec3_from(
		[
			&test_data
		](
			std::size_t const _index
		)
		{
			vec3 result{
				fcppt::no_init()
			};

			std::memcpy(
				fcppt::cast::to_char_ptr<
					unsigned char *
				>(
					result.storage().data()
				),
				test_data.data()
				+ // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				_index,
				3 * sizeof(float)
			);

			return
				result;
		}
	);

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wfloat-equal)

	// TODO(philipp)
	CHECK(
		vec3_from(
			0
		)
		==
		vec3{-1.F,1.F,0.F}
	);

	CHECK(
		vec3_from(
			stride.get()
		)
		==
		vec3{-1.F,-1.F,0.F}
	);

	CHECK(
		vec3_from(
			2 * stride.get()
		)
		==
		vec3{1.F,1.F,0.F}
	);

FCPPT_PP_POP_WARNING
}
