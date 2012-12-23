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


#include <sge/opengl/enable.hpp>
#include <sge/opengl/init_srgb.hpp>
#include <sge/opengl/optional_enum.hpp>
#include <sge/opengl/srgb_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/renderer/logger.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>


void
sge::opengl::init_srgb(
	sge::opengl::context::system::object &_system_context,
	sge::renderer::pixel_format::srgb const _srgb
)
{
	if(
		_srgb
		==
		sge::renderer::pixel_format::srgb::no
	)
		return;

	sge::opengl::srgb_context const &srgb_context(
		sge::opengl::context::use<
			sge::opengl::srgb_context
		>(
			_system_context
		)
	);

	sge::opengl::optional_enum const srgb_flag(
		srgb_context.flag()
	);

	if(
		!srgb_flag
	)
	{
		if(
			_srgb
			==
			sge::renderer::pixel_format::srgb::try_
		)
		{
			FCPPT_LOG_WARNING(
				sge::renderer::logger(),
				fcppt::log::_
					<< FCPPT_TEXT("srgb::try_ was specified but srgb is not supported!")
			);

			return;
		}
		else
			throw sge::renderer::unsupported(
				FCPPT_TEXT("srgb sampling"),
				FCPPT_TEXT("GL_VERSION_3_0"),
				FCPPT_TEXT("EXT_framebuffer_sRGB")
			);
	}

	sge::opengl::enable(
		*srgb_flag
	);
}
