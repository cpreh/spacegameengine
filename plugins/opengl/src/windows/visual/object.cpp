//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/opengl/windows/visual/choose_and_set_format.hpp>
#include <sge/opengl/windows/visual/object.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <awl/backends/windows/windows.hpp>
#include <awl/backends/windows/visual/object.hpp>


sge::opengl::windows::visual::object::object(
	sge::opengl::wgl::visual::config const &_config,
	sge::renderer::pixel_format::object const &_format
)
:
	awl::backends::windows::visual::object(),
	config_(
		_config
	),
	format_(
		_format
	)
{
}

sge::opengl::windows::visual::object::~object()
{
}

void
sge::opengl::windows::visual::object::apply(
	HWND const _hwnd
) const
{
	sge::opengl::windows::visual::choose_and_set_format(
		config_,
		_hwnd,
		format_
	);
}
