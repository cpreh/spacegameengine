//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/occlusion_query/config_fwd.hpp>
#include <sge/opengl/occlusion_query/create_id.hpp>
#include <sge/opengl/occlusion_query/delete_id.hpp>
#include <sge/opengl/occlusion_query/holder.hpp>
#include <sge/opengl/occlusion_query/id.hpp>


sge::opengl::occlusion_query::holder::holder(
	sge::opengl::occlusion_query::config const &_config
)
:
	config_(
		_config
	),
	id_(
		sge::opengl::occlusion_query::create_id(
			config_
		)
	)
{
}

sge::opengl::occlusion_query::holder::~holder()
{
	sge::opengl::occlusion_query::delete_id(
		config_,
		id_
	);
}

sge::opengl::occlusion_query::id
sge::opengl::occlusion_query::holder::id() const
{
	return
		id_;
}
