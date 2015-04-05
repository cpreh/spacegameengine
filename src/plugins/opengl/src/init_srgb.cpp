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


#include <sge/opengl/common.hpp>
#include <sge/opengl/enable.hpp>
#include <sge/opengl/init_srgb.hpp>
#include <sge/opengl/logger.hpp>
#include <sge/opengl/srgb_context.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
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

	fcppt::maybe(
		srgb_context.flag(),
		[
			_srgb
		]{
			if(
				_srgb
				==
				sge::renderer::pixel_format::srgb::try_
			)
			{
				FCPPT_LOG_WARNING(
					sge::opengl::logger(),
					fcppt::log::_
						<< FCPPT_TEXT("srgb::try_ was specified but srgb is not supported!")
				);
			}
			else
				throw sge::renderer::unsupported(
					FCPPT_TEXT("srgb sampling"),
					FCPPT_TEXT("GL_VERSION_3_0"),
					FCPPT_TEXT("EXT_framebuffer_sRGB")
				);
		},
		[](
			GLenum const _srgb_flag
		)
		{
			sge::opengl::enable(
				_srgb_flag
			);
		}
	);
}
