/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <sge/opengl/glx/visual/choose.hpp>
#include <sge/renderer/exception.hpp>
#include <awl/backends/x11/display.hpp>
#include <awl/backends/x11/screen.hpp>
#include <awl/backends/x11/visual/info_unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <utility>
#include <fcppt/config/external_end.hpp>


awl::backends::x11::visual::info_unique_ptr
sge::opengl::glx::visual::choose(
	awl::backends::x11::display const &_display,
	awl::backends::x11::screen const _screen,
	sge::opengl::glx::visual::attribute_container const &_attributes
)
{
	awl::backends::x11::visual::info_unique_ptr info(
		::glXChooseVisual(
			_display.get(),
			_screen.get(),
			const_cast<
				int *
			>(
				_attributes.data()
			)
		)
	);

	if(
		!info
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("glXChooseVisual() failed!")
		);

	return
		std::move(
			info
		);
}
