/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SYSTEMS_VIEWPORT_RESIZE_MANAGER_HPP_INCLUDED
#define SGE_SYSTEMS_VIEWPORT_RESIZE_MANAGER_HPP_INCLUDED

#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/target_ptr.hpp>
#include <sge/systems/viewport/manager.hpp>
#include <awl/event/resize_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace systems
{
namespace viewport
{

class resize_manager
:
	public sge::systems::viewport::manager
{
	FCPPT_NONCOPYABLE(
		resize_manager
	)
public:
	explicit resize_manager(
		sge::renderer::device_ptr
	);

	~resize_manager();
private:
	void
	on_resize(
		awl::event::resize const &
	);

	sge::renderer::target_ptr const target_;

	fcppt::signal::scoped_connection const resize_connection_;
};

}
}
}

#endif
