/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/glx/visual/create.hpp>
#include <sge/opengl/glx/visual/choose.hpp>
#include <sge/opengl/glx/visual/make_attributes.hpp>
#include <sge/renderer/parameters_fwd.hpp>
#include <awl/backends/x11/system/object.hpp>
#include <awl/backends/x11/visual/wrapped.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/container/raw_vector_impl.hpp>


awl::visual::object_unique_ptr
sge::opengl::glx::visual::create(
	awl::backends::x11::system::object &_awl_system,
	sge::renderer::parameters const &_parameters
)
{
	return
		awl::visual::object_unique_ptr(
			fcppt::make_unique_ptr<
				awl::backends::x11::visual::wrapped
			>(
				sge::opengl::glx::visual::choose(
					_awl_system.display(),
					_awl_system.screen(),
					sge::opengl::glx::visual::make_attributes(
						_parameters
					)
				)
			)
		);
}
