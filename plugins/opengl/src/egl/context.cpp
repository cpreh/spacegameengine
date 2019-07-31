//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/backend/context.hpp>
#include <sge/opengl/backend/current.hpp>
#include <sge/opengl/backend/current_unique_ptr.hpp>
#include <sge/opengl/egl/context.hpp>
#include <sge/opengl/egl/current.hpp>
#include <sge/opengl/egl/surface.hpp>
#include <sge/opengl/egl/surface_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::context::context(
	EGLDisplay const _display,
	EGLConfig const _config,
	sge::opengl::egl::surface_unique_ptr &&_surface
)
:
	sge::opengl::backend::context(),
	display_{
		_display
	},
	surface_{
		std::move(
			_surface
		)
	},
	context_{
		_display,
		_config
	}
{
}

sge::opengl::egl::context::~context()
{
}

sge::opengl::backend::current_unique_ptr
sge::opengl::egl::context::activate()
{
	context_.activate(
		surface_->get()
	);

	return
		fcppt::unique_ptr_to_base<
			sge::opengl::backend::current
		>(
			fcppt::make_unique_ptr<
				sge::opengl::egl::current
			>(
				display_,
				surface_->get()
			)
		);
}

void
sge::opengl::egl::context::deactivate(
	sge::opengl::backend::current_unique_ptr &&
)
{
	context_.deactivate();
}
