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


#ifndef SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_IMPL_HPP_INCLUDED

#include "basic.hpp"
#include "pool.hpp"
#include <fcppt/container/bitfield/basic_impl.hpp>

template<
	typename Types
>
sge::d3d9::texture::basic<Types>::basic(
	IDirect3DDevice9 *const _device,
	parameters_type const &_parameters
)
:
	Types::base(),
	d3d9::texture::base(0),
	d3d9::resource(
		texture::pool(
			_parameters.resource_flags(),
			_parameters.capabilities()
		)
	),
	device_(_device),
	parameters_(_parameters)
{
}

template<
	typename Types
>
sge::d3d9::texture::basic<Types>::~basic()
{
}

template<
	typename Types
>
typename sge::d3d9::texture::basic<Types>::parameters_type const &
sge::d3d9::texture::basic<Types>::parameters() const
{
	return parameters_;
}

template<
	typename Types
>
IDirect3DDevice9 *
sge::d3d9::texture::basic<Types>::device() const
{
	return device_;
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::on_reset()
{
	this->reset_base(
		this->do_reset()
	);
}

template<
	typename Types
>
void
sge::d3d9::texture::basic<Types>::on_loss()
{
#if 0
	this->do_loss();
#endif
}

template<
	typename Types
>
sge::renderer::resource_flags_field const
sge::d3d9::texture::basic<Types>::resource_flags() const
{
	return this->parameters().resource_flags();
}

#endif
