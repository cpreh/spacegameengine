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


#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/create_planar.hpp>
#include <sge/opengl/texture/planar.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters_fwd.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>


sge::renderer::texture::planar_unique_ptr
sge::opengl::texture::create_planar(
	sge::opengl::texture::basic_parameters const &_basic_parameters,
	sge::renderer::texture::planar_parameters const &_parameters
)
{
	return
		sge::renderer::texture::planar_unique_ptr(
			fcppt::make_unique_ptr<
				sge::opengl::texture::planar
			>(
				fcppt::cref(
					_basic_parameters
				),
				fcppt::cref(
					_parameters
				)
			)
		);
}
