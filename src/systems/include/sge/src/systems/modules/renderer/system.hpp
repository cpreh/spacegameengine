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


#ifndef SGE_SRC_SYSTEMS_MODULES_RENDERER_SYSTEM_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_RENDERER_SYSTEM_HPP_INCLUDED

#include <sge/plugin/manager_fwd.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/plugin_ptr.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/system_ptr.hpp>
#include <sge/src/systems/plugin_cache_fwd.hpp>
#include <sge/src/systems/modules/renderer/system_fwd.hpp>
#include <sge/systems/renderer_fwd.hpp>
#include <sge/window/parameters_fwd.hpp>
#include <awl/system/object_fwd.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace renderer
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	system(
		sge::systems::plugin_cache &,
		sge::plugin::manager &,
		sge::systems::renderer const &
	);

	awl::window::instance_shared_ptr const
	create_window(
		awl::system::object &,
		sge::window::parameters const &
	);

	sge::renderer::system &
	get() const;
private:
	sge::renderer::plugin_ptr const plugin_;

	sge::renderer::parameters const renderer_parameters_;

	sge::renderer::system_ptr const renderer_system_;
};

}
}
}
}

#endif
