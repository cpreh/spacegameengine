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


#include <sge/renderer/device.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/context/scoped.hpp>
#include <sge/renderer/target/base_fwd.hpp>


sge::renderer::context::scoped::scoped(
	sge::renderer::device &_device,
	sge::renderer::target::base &_target
)
:
	device_(
		_device
	),
	context_(
		device_.begin_rendering(
			_target
		)
	)
{
}

sge::renderer::context::scoped::~scoped()
{
	device_.end_rendering(
		*context_
	);
}

sge::renderer::context::object &
sge::renderer::context::scoped::get() const
{
	return
		*context_;
}
