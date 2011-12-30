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


#include <sge/renderer/texture/address_mode.hpp>
#include <sge/renderer/texture/address_mode3.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>


sge::renderer::texture::address_mode3::address_mode3(
	texture::address_mode::type const _address_mode
)
:
	address_mode_s_(
		texture::address_mode_s(
			_address_mode
		)
	),
	address_mode_t_(
		texture::address_mode_t(
			_address_mode
		)
	),
	address_mode_u_(
		texture::address_mode_u(
			_address_mode
		)
	)
{
}

sge::renderer::texture::address_mode3::address_mode3(
	texture::address_mode_s const _address_mode_s,
	texture::address_mode_t const _address_mode_t,
	texture::address_mode_u const _address_mode_u
)
:
	address_mode_s_(_address_mode_s),
	address_mode_t_(_address_mode_t),
	address_mode_u_(_address_mode_u)
{
}

sge::renderer::texture::address_mode_s const
sge::renderer::texture::address_mode3::address_mode_s() const
{
	return address_mode_s_;
}

sge::renderer::texture::address_mode_t const
sge::renderer::texture::address_mode3::address_mode_t() const
{
	return address_mode_t_;
}

sge::renderer::texture::address_mode_u const
sge::renderer::texture::address_mode3::address_mode_u() const
{
	return address_mode_u_;
}
