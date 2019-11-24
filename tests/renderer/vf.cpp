//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/bgra8_format.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/vf/color.hpp>
#include <sge/renderer/vf/format.hpp>
#include <sge/renderer/vf/part.hpp>
#include <sge/renderer/vf/pos.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
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
#include <sge/renderer/vf/dynamic/part_list.hpp>
#include <sge/renderer/vf/dynamic/pos.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <catch2/catch.hpp>
#include <metal/list/list.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


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
	typedef
	sge::renderer::vf::pos<
		float,
		3
	>
	pos3_type;

	typedef
	sge::image::color::bgra8_format
	color_format;

	typedef
	sge::renderer::vf::color<
		color_format
	>
	color_type;

	typedef
	sge::renderer::vf::part<
		metal::list<
			pos3_type,
			color_type
		>
	>
	format_part;

	static_assert(
		std::is_same_v<
			format_part::strides,
			metal::list<
				static_size<
					3 * sizeof(float)
				>,
				static_size<
					4
				>
			>
		>
	);

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

	typedef
	sge::renderer::vf::format<
		metal::list<
			format_part
		>
	>
	format;

	sge::renderer::vf::dynamic::format const dynamic_format{
		sge::renderer::vf::dynamic::make_format<
			format
		>()
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
										sge::renderer::vf::dynamic::element_count{
											3u
										}
									}
								}
							}
						},
						sge::renderer::vf::dynamic::offset{
							0u
						}
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
				sge::renderer::vf::dynamic::stride{
					3 * sizeof(float)
					+ 4
				}
			}
		}
	);
}
