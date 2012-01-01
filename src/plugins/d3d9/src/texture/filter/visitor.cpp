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


#include <sge/d3d9/texture/filter/anisotropic.hpp>
#include <sge/d3d9/texture/filter/normal.hpp>
#include <sge/d3d9/texture/filter/visitor.hpp>


sge::d3d9::texture::filter::visitor::visitor(
	IDirect3DDevice9 *const _device,
	renderer::texture::stage const _stage
)
:
	device_(_device),
	stage_(_stage)
{
}

sge::d3d9::texture::filter::visitor::result_type
sge::d3d9::texture::filter::visitor::operator()(
	renderer::texture::filter::anisotropic::object const &_object
) const
{
	filter::anisotropic(
		device_,
		stage_,
		_object
	);
}

sge::d3d9::texture::filter::visitor::result_type
sge::d3d9::texture::filter::visitor::operator()(
	renderer::texture::filter::normal::object const &_object
) const
{
	filter::normal(
		device_,
		stage_,
		_object
	);
}
