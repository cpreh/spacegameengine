//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/wgl/visual/config_fwd.hpp>
#include <sge/opengl/windows/visual/create.hpp>
#include <sge/opengl/windows/visual/object.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


awl::visual::object_unique_ptr
sge::opengl::windows::visual::create(
	sge::opengl::wgl::visual::config const &_config,
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::visual::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::windows::visual::object
			>(
				_config,
				_pixel_format
			)
		);
}
