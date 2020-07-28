//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/object_ref.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/object_reference.hpp>


sge::opengl::texture::basic_parameters::basic_parameters(
	fcppt::log::object_reference const _log,
	sge::opengl::context::object_ref const _context
)
:
	log_{
		_log
	},
	context_(
		_context
	)
{
}

fcppt::log::object &
sge::opengl::texture::basic_parameters::log() const
{
	return
		log_.get();
}

sge::opengl::context::object &
sge::opengl::texture::basic_parameters::context() const
{
	return
		context_.get();
}
