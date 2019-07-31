//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/egl/visual/base.hpp>
#include <sge/opengl/egl/visual/choose_config.hpp>
#include <sge/opengl/egl/visual/make_attributes.hpp>
#include <sge/renderer/visual_base.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <EGL/egl.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::egl::visual::base::base(
	fcppt::log::object &_log,
	EGLDisplay const _egl_display,
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	sge::renderer::visual_base(
		_pixel_format
	),
	config_(
		sge::opengl::egl::visual::choose_config(
			_log,
			_egl_display,
			sge::opengl::egl::visual::make_attributes(
				_pixel_format
			)
		)
	)
{
}

sge::opengl::egl::visual::base::~base()
{
}

EGLConfig
sge::opengl::egl::visual::base::config() const
{
	return
		config_;
}
