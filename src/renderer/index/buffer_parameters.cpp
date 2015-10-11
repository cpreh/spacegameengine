/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/renderer/index/buffer_parameters.hpp>
#include <sge/renderer/index/count.hpp>
#include <sge/renderer/index/dynamic/format.hpp>


sge::renderer::index::buffer_parameters::buffer_parameters(
	sge::renderer::index::dynamic::format const _format,
	sge::renderer::index::count const _count,
	sge::renderer::resource_flags_field const &_flags
)
:
	format_(
		_format
	),
	count_(
		_count
	),
	flags_(
		_flags
	)
{
}

sge::renderer::index::dynamic::format
sge::renderer::index::buffer_parameters::format() const
{
	return
		format_;
}

sge::renderer::index::count
sge::renderer::index::buffer_parameters::count() const
{
	return
		count_;
}

sge::renderer::resource_flags_field const &
sge::renderer::index::buffer_parameters::flags() const
{
	return
		flags_;
}
