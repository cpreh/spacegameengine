//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <sge/opengl/glx/visual/choose.hpp>
#include <sge/opengl/glx/visual/create.hpp>
#include <sge/opengl/glx/visual/make_attributes.hpp>
#include <sge/opengl/glx/visual/object.hpp>
#include <sge/opengl/glx/visual/optional_srgb_flag.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>


awl::visual::object_unique_ptr
sge::opengl::glx::visual::create(
	sge::opengl::glx::visual::optional_srgb_flag const _srgb_flag,
	awl::backends::x11::system::object &_awl_system,
	sge::renderer::pixel_format::object const &_format
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::visual::object
		>(
			fcppt::make_unique_ptr<
				sge::opengl::glx::visual::object
			>(
				sge::opengl::glx::visual::choose(
					_awl_system.display().get(),
					_awl_system.screen(),
					sge::opengl::glx::visual::make_attributes(
						_srgb_flag,
						_format
					)
				),
				_format
			)
		);
}
