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


#include <sge/renderer/add_depth_stencil_surface_to_target.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/optional_dim2.hpp>
#include <sge/renderer/target.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/dim/basic_impl.hpp>


void
sge::renderer::add_depth_stencil_surface_to_target(
	renderer::device &_device,
	renderer::target &_target,
	renderer::depth_stencil_format::type const _format
)
{
	renderer::optional_dim2 const dim(
		_target.size()
	);

	if(
		!dim
	)
		throw sge::renderer::exception(
			FCPPT_TEXT("To add a depth_stencil_surface with the correct dimensions to a target, ")
			FCPPT_TEXT("you should add a color_surface first!")
		);

	_target.depth_stencil_surface(
		_device.create_depth_stencil_surface(
			*dim,
			_format
		)
	);
}
