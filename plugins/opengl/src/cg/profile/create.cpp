//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/cg/profile/object.hpp>
#include <sge/cg/profile/shader_type.hpp>
#include <sge/opengl/cg/profile/convert_shader_type.hpp>
#include <sge/opengl/cg/profile/create.hpp>
#include <sge/opengl/cg/profile/get_latest.hpp>


sge::cg::profile::object
sge::opengl::cg::profile::create(
	sge::cg::profile::shader_type const _shader_type
)
{
	return
		sge::cg::profile::object(
			sge::opengl::cg::profile::get_latest(
				sge::opengl::cg::profile::convert_shader_type(
					_shader_type
				)
			)
		);
}
