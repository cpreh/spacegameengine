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


#include "../address_mode.hpp"
#include "../../d3dinclude.hpp"
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/container/array_impl.hpp>
#include <fcppt/container/index_map_impl.hpp>

namespace
{

unsigned
index(
	D3DSAMPLERSTATETYPE
);

}

sge::d3d9::state::address_mode::address_mode()
:
	levels_()
{
}

sge::d3d9::state::address_mode::~address_mode()
{
}

bool
sge::d3d9::state::address_mode::update(
	renderer::stage const _stage,
	D3DSAMPLERSTATETYPE const _type,
	D3DTEXTUREADDRESS const _value
)
{
	address_level const default_level =
	{{
		D3DTADDRESS_WRAP,
		D3DTADDRESS_WRAP,
		D3DTADDRESS_WRAP
	}};

	D3DTEXTUREADDRESS &previous(
		levels_.get_default(
			_stage.get(),
			default_level
		)
		[
			::index(
				_type
			)
		]
	);

	if(
		previous
		!= _value
	)
	{
		previous
			= _value;

		return true;
	}

	return false;
}

namespace
{

unsigned
index(
	D3DSAMPLERSTATETYPE const _type
)
{
	switch(
		_type
	)
	{
	case D3DSAMP_ADDRESSU:
		return 0;
	case D3DSAMP_ADDRESSV:
		return 1;
	case D3DSAMP_ADDRESSW:
		return 2;
	default:
		break;
	}

	FCPPT_ASSERT_UNREACHABLE
}

}
