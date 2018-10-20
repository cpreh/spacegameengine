/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <sge/opengl/egl/visual/to_config.hpp>
#include <awl/visual/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_cross.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


EGLConfig
sge::opengl::egl::visual::to_config(
	fcppt::log::object &_log,
	EGLDisplay const _egl_display,
	awl::visual::object const &_visual
)
{
	return
		fcppt::optional::maybe(
			fcppt::cast::dynamic_cross<
				sge::opengl::egl::visual::base const
			>(
				_visual
			),
			[
				&_log,
				_egl_display
			]
			{
				FCPPT_LOG_WARNING(
					_log,
					fcppt::log::out
						<< FCPPT_TEXT("Visual is not an EGL visual.")
				);

				return
					sge::opengl::egl::visual::choose_config(
						_log,
						_egl_display,
						sge::opengl::egl::attribute_vector{
							EGL_NONE
						}
					);
			},
			[](
				fcppt::reference<
					sge::opengl::egl::visual::base const
				> const _sge_visual
			)
			{
				return
					_sge_visual.get().config();
			}
		);
}
