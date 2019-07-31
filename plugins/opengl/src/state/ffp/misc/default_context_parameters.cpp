//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/state/ffp/misc/default_context_parameters.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::opengl::state::ffp::misc::default_context_parameters::default_context_parameters(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context
)
:
	log_{
		_log
	},
	context_{
		_context
	}
{
}

fcppt::log::object &
sge::opengl::state::ffp::misc::default_context_parameters::log() const
{
	return
		log_.get();
}

sge::opengl::context::object &
sge::opengl::state::ffp::misc::default_context_parameters::context() const
{
	return
		context_.get();
}
