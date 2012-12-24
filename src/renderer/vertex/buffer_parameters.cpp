/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/vertex/buffer_parameters.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>


sge::renderer::vertex::buffer_parameters::buffer_parameters(
	sge::renderer::vertex::declaration const &_declaration,
	sge::renderer::vf::dynamic::part_index const _part,
	sge::renderer::vertex::count const _count,
	sge::renderer::resource_flags_field const &_flags
)
:
	declaration_(
		_declaration
	),
	part_(
		_part
	),
	count_(
		_count
	),
	flags_(
		_flags
	)
{
}

sge::renderer::vertex::declaration const &
sge::renderer::vertex::buffer_parameters::declaration() const
{
	return declaration_;
}

sge::renderer::vf::dynamic::part_index const
sge::renderer::vertex::buffer_parameters::part() const
{
	return part_;
}

sge::renderer::vertex::count const
sge::renderer::vertex::buffer_parameters::count() const
{
	return count_;
}

sge::renderer::resource_flags_field const &
sge::renderer::vertex::buffer_parameters::flags() const
{
	return flags_;
}
