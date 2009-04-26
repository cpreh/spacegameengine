/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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



#include <sge/renderer/vf/dynamic_element.hpp>

sge::renderer::vf::dynamic_element::dynamic_element(
	dynamic_any const &info_,
	vf::role::type const role_,
	vertex_size const index_)
:
	info_(info_),
	role_(role_),
	index_(index_)
{}
	
sge::renderer::vf::dynamic_any const &
sge::renderer::vf::dynamic_element::info() const
{
	return info_;
}

sge::renderer::vf::role::type
sge::renderer::vf::dynamic_element::role() const
{
	return role_;
}

sge::renderer::vf::vertex_size
sge::renderer::vf::dynamic_element::index() const
{
	return index_;
}
