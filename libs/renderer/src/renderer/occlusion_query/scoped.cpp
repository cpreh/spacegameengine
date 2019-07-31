//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/occlusion_query/object.hpp>
#include <sge/renderer/occlusion_query/scoped.hpp>


sge::renderer::occlusion_query::scoped::scoped(
	sge::renderer::occlusion_query::object &_query
)
:
	query_(
		_query
	)
{
	query_.begin();
}

sge::renderer::occlusion_query::scoped::~scoped()
{
	query_.end();
}

sge::renderer::occlusion_query::object &
sge::renderer::occlusion_query::scoped::get() const
{
	return
		query_;
}
