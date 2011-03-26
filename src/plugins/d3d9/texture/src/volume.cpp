/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../volume.hpp"
#include "../basic_impl.hpp"
#include "../lock_volume.hpp"
#include "../unlock_volume.hpp"
#include "../volume_types.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/variant/object_impl.hpp>

sge::d3d9::texture::volume::volume(
	IDirect3DDevice9 *const _device,
	renderer::texture::volume_parameters const &_params
)
:
	texture::volume_basic(
		_device,
		_params
	)
{
}

sge::d3d9::texture::volume::~volume()
{
}

sge::d3d9::texture::volume::dim const
sge::d3d9::texture::volume::size() const
{
	return this->parameters().size();
}

sge::d3d9::texture::volume::view const
sge::d3d9::texture::volume::lock(
	lock_area const &_box,
	renderer::lock_mode::type const _mode
)
{
	return
		this->lock_impl(
			this->lock_function(),
			_box,
			_mode
		);
}

sge::d3d9::texture::volume::const_view const
sge::d3d9::texture::volume::lock(
	lock_area const &_box
) const
{
	return
		this->lock_impl(
			this->lock_function(),
			_box
		);
}

void
sge::d3d9::texture::volume::unlock() const
{
	this->unlock_impl(
		std::tr1::bind(
			texture::unlock_volume,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2
		)
	);
}

sge::d3d9::texture::volume_basic::lock_function const
sge::d3d9::texture::volume::lock_function() const
{
	return
		std::tr1::bind(
			texture::lock_volume,
			std::tr1::placeholders::_1,
			std::tr1::placeholders::_2,
			std::tr1::placeholders::_3,
			std::tr1::placeholders::_4
		);
}

template class
sge::d3d9::texture::basic<
	sge::d3d9::texture::volume_types
>;
