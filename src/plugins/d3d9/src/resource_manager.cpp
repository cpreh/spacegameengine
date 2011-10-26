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


#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/resource_manager.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sge::d3d9::resource_manager::resource_manager()
:
	resources_()
{
}

sge::d3d9::resource_manager::~resource_manager()
{
}

void
sge::d3d9::resource_manager::add(
	d3d9::resource &_resource
)
{
	resources_.push_back(
		_resource
	);
}

void
sge::d3d9::resource_manager::release()
{
	std::for_each(
		resources_.begin(),
		resources_.end(),
		std::tr1::bind(
			&resource::loss,
			std::tr1::placeholders::_1
		)
	);
}

void
sge::d3d9::resource_manager::reinit()
{
	std::for_each(
		resources_.begin(),
		resources_.end(),
		std::tr1::bind(
			&resource::reset,
			std::tr1::placeholders::_1
		)
	);
}
