//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/call_fun_ref.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/occlusion_query/config.hpp>
#include <sge/opengl/occlusion_query/create_id.hpp>
#include <sge/opengl/occlusion_query/id.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>


sge::opengl::occlusion_query::id
sge::opengl::occlusion_query::create_id(
	sge::opengl::occlusion_query::config const &_config
)
{
	GLuint id{};

	sge::opengl::call_fun_ref(
		_config.gen_queries(),
		1,
		&id
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("Generating a query failed"),
		sge::renderer::exception
	)

	return
		sge::opengl::occlusion_query::id(
			id
		);
}
