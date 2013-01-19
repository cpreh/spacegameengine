/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/opengl/context/use.hpp>
#include <sge/opengl/texture/basic_parameters.hpp>
#include <sge/opengl/texture/create_volume.hpp>
#include <sge/opengl/texture/volume.hpp>
#include <sge/opengl/texture/volume_context.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/texture/volume.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>
#include <sge/renderer/texture/volume_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sge::renderer::texture::volume_unique_ptr
sge::opengl::texture::create_volume(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::volume_parameters const &_parameters
)
{
	if(
		!sge::opengl::context::use<
			sge::opengl::texture::volume_context
		>(
			_basic_parameters.system_context()
		).have_volume_texture()
	)
		throw sge::renderer::unsupported(
			FCPPT_TEXT("volume texture"),
			FCPPT_TEXT("1.2"),
			FCPPT_TEXT("")
		);

	return
		sge::renderer::texture::volume_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::texture::volume
			>(
				_basic_parameters,
				_parameters
			)
		);
}
