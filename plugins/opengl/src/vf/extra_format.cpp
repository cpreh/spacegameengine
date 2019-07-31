//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_base_type_sge.hpp>
#include <sge/opengl/vf/convert_color_format.hpp>
#include <sge/opengl/vf/convert_element_type.hpp>
#include <sge/opengl/vf/extra_format.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/extra_any.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <fcppt/variant/match.hpp>


GLenum
sge::opengl::vf::extra_format(
	sge::renderer::vf::dynamic::extra_any const &_any
)
{
	return
		fcppt::variant::match(
			_any,
			[](
				sge::renderer::vf::dynamic::vector const &_vector
			)
			{
				return
					sge::opengl::vf::convert_element_type(
						_vector.element_type()
					);
			},
			[](
				sge::renderer::vf::dynamic::color const &_color
			)
			{
				return
					sge::opengl::convert::color_base_type_sge(
						sge::opengl::vf::convert_color_format(
							_color.color_format()
						)
					).get();
			}
		);
}
