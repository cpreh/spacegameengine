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


#ifndef SGE_RENDERER_TEXTURE_ADDRESS_MODE3_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_ADDRESS_MODE3_HPP_INCLUDED

#include <sge/renderer/texture/address_mode3_fwd.hpp>
#include <sge/renderer/texture/address_mode_s.hpp>
#include <sge/renderer/texture/address_mode_t.hpp>
#include <sge/renderer/texture/address_mode_u.hpp>
#include <sge/renderer/texture/address_mode.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{

class address_mode3
{
public:
	SGE_SYMBOL
	explicit
	address_mode3(
		texture::address_mode::type
	);

	SGE_SYMBOL
	address_mode3(
		texture::address_mode_s,
		texture::address_mode_t,
		texture::address_mode_u
	);

	SGE_SYMBOL
	texture::address_mode_s const
	address_mode_s() const;

	SGE_SYMBOL
	texture::address_mode_t const
	address_mode_t() const;

	SGE_SYMBOL
	texture::address_mode_u const
	address_mode_u() const;
private:
	texture::address_mode_s address_mode_s_;

	texture::address_mode_t address_mode_t_;

	texture::address_mode_u address_mode_u_;
};

}
}
}

#endif
