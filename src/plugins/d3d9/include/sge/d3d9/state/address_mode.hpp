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


#ifndef SGE_D3D9_STATE_ADDRESS_MODE_HPP_INCLUDED
#define SGE_D3D9_STATE_ADDRESS_MODE_HPP_INCLUDED

#include <sge/d3d9/state/address_mode_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/array_decl.hpp>
#include <fcppt/container/index_map_decl.hpp>


namespace sge
{
namespace d3d9
{
namespace state
{

class address_mode
{
	FCPPT_NONCOPYABLE(
		address_mode
	);
public:
	address_mode();

	~address_mode();

	bool
	update(
		renderer::texture::stage,
		D3DSAMPLERSTATETYPE,
		D3DTEXTUREADDRESS
	);
private:
	typedef fcppt::container::array<
		D3DTEXTUREADDRESS,
		3
	> address_level;

	typedef fcppt::container::index_map<
		address_level
	> level_map;

	level_map levels_;
};

}
}
}

#endif
