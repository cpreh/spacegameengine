//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/set_defaults.hpp>
#include <sge/opengl/state/core/set_defaults.hpp>
#include <sge/opengl/state/ffp/set_defaults.hpp>
#include <fcppt/log/object_fwd.hpp>


void
sge::opengl::state::set_defaults(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context
)
{
	sge::opengl::state::core::set_defaults(
		_context
	);

	sge::opengl::state::ffp::set_defaults(
		_log,
		_context
	);
}
