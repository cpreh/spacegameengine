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


#include <sge/renderer/vf/dynamic_vector.hpp>

sge::renderer::vf::dynamic_vector::dynamic_vector(
	vf::element_type::type const element_type_,
	vertex_size const elements_)
:
	element_type_(element_type_),
	elements_(elements_)
{}

sge::renderer::vf::element_type::type
sge::renderer::vf::dynamic_vector::element_type() const
{
	return element_type_;
}

sge::renderer::vf::vertex_size
sge::renderer::vf::dynamic_vector::elements() const
{
	return elements_;
}
