//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/attribute_vector.hpp>
#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <sge/opengl/egl/visual/to_config.hpp>
#include <awl/visual/object.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_cross.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
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
