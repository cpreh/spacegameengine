//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/context_ref.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/scoped_current.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::backend::scoped_current::scoped_current(
	sge::opengl::backend::context_ref const _context
)
:
	context_(
		_context
	),
	current_(
		context_.get().activate()
	)
{
}

sge::opengl::backend::scoped_current::~scoped_current()
{
	context_.get().deactivate(
		std::move(
			current_
		)
	);
}

sge::opengl::backend::current &
sge::opengl::backend::scoped_current::get() const
{
	return
		*current_;
}
