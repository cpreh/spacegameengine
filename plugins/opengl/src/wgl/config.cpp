//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/wgl/config.hpp>
#include <sge/opengl/wgl/visual/config.hpp>


sge::opengl::wgl::config::config(
	sge::opengl::wgl::visual::config const &_visual_config
)
:
	visual_config_(
		_visual_config
	)
{
}

sge::opengl::wgl::visual::config const &
sge::opengl::wgl::config::visual_config() const
{
	return
		visual_config_;
}
