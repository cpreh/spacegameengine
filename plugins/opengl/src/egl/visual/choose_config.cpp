//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


EGLConfig
sge::opengl::egl::visual::choose_config(
	fcppt::log::object &_log,
	EGLDisplay const _display, // NOLINT(misc-misplaced-const)
	sge::opengl::egl::attribute_vector const &_attributes
)
{
	EGLConfig result{};

	EGLint num_config{};

	if(
		::eglChooseConfig(
			_display,
			_attributes.data(),
			&result,
			1,
			&num_config
		)
		!=
		EGL_TRUE
	)
	{
		throw
			sge::renderer::exception(
				FCPPT_TEXT("eglChooseConfig failed")
			);
	}

	if(
		num_config
		<=
		0
	)
	{
		throw
			sge::renderer::exception(
				FCPPT_TEXT("No matching EGL configs")
			);
	}

	if(
		num_config
		!=
		1
	)
	{
		FCPPT_LOG_WARNING(
			_log,
			fcppt::log::out
				<< FCPPT_TEXT("Multiple EGL configs are matching. Choosing the first one.")
		);
	}

	return
		result;
}
