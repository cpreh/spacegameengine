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


#include "../resource.hpp"
#include "../d3dinclude.hpp"

sge::d3d9::resource::resource(
	D3DPOOL const _pool
)
:
	pool_(_pool)
{
}

sge::d3d9::resource::~resource()
{
}

void
sge::d3d9::resource::loss()
{
	if(
		this->needs_reset()
	)
		this->on_loss();
}

void
sge::d3d9::resource::reset()
{
	if(
		this->needs_reset()
	)
		this->on_reset();
}

D3DPOOL
sge::d3d9::resource::pool() const
{
	return pool_;
}

bool
sge::d3d9::resource::needs_reset() const
{
	return
		this->pool()
		!= D3DPOOL_MANAGED;
}
