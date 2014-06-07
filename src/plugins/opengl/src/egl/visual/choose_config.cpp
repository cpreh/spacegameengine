/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/logger.hpp>
#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


EGLConfig
sge::opengl::egl::visual::choose_config(
	EGLDisplay const _display,
	sge::opengl::egl::attribute_vector const &_attributes
)
{
	EGLConfig result;

	EGLint num_config;

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
		throw
			sge::renderer::exception(
				FCPPT_TEXT("eglChooseConfig failed")
			);

	if(
		num_config
		<=
		0
	)
		throw
			sge::renderer::exception(
				FCPPT_TEXT("No matching EGL configs")
			);

	if(
		num_config
		!=
		1
	)
		FCPPT_LOG_WARNING(
			sge::opengl::logger(),
			fcppt::log::_
				<< FCPPT_TEXT("Multiple EGL configs are matching. Choosing the first one.")
		);

	return
		result;
}
