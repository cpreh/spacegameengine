/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/renderer/context/ffp.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/target/base_fwd.hpp>


sge::renderer::context::scoped_ffp::scoped_ffp(
	sge::renderer::device::ffp &_device,
	sge::renderer::target::base &_target
)
:
	device_(
		_device
	),
	context_(
		device_.begin_rendering_ffp(
			_target
		)
	)
{
}

sge::renderer::context::scoped_ffp::~scoped_ffp()
{
	device_.end_rendering_ffp(
		*context_
	);
}

sge::renderer::context::ffp &
sge::renderer::context::scoped_ffp::get() const
{
	return
		*context_;
}
