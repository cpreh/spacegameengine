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


#ifndef SGE_SRC_SYSTEMS_MODULES_RENDERER_DEVICE_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_RENDERER_DEVICE_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/device_ptr.hpp>
#include <sge/src/systems/modules/renderer/device_fwd.hpp>
#include <sge/src/systems/modules/renderer/system_fwd.hpp>
#include <sge/src/systems/modules/window/object_fwd.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace renderer
{

class device
{
	FCPPT_NONCOPYABLE(
		device
	);
public:
	device(
		sge::systems::renderer const &,
		sge::systems::modules::renderer::system const &,
		sge::systems::modules::window::object const &
	);

	~device();

	sge::renderer::device &
	get() const;

	sge::viewport::manager &
	viewport_manager();
private:
	sge::renderer::device_ptr const renderer_device_;

	sge::viewport::manager viewport_manager_;
};

}
}
}
}

#endif
