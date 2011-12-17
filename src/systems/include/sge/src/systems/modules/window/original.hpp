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


#ifndef SGE_SRC_SYSTEMS_MODULES_WINDOW_ORIGINAL_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_WINDOW_ORIGINAL_HPP_INCLUDED

#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/window/base.hpp>
#include <sge/window/object_ptr.hpp>
#include <sge/window/parameters_fwd.hpp>
#include <sge/window/system.hpp>
#include <awl/event/processor_scoped_ptr.hpp>
#include <awl/window/instance_shared_ptr.hpp>
#include <awl/window/event/processor_scoped_ptr.hpp>
#include <awl/system/object_scoped_ptr.hpp>
#include <awl/system/event/processor_scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace window
{

class original
:
	public sge::systems::modules::window::base
{
	FCPPT_NONCOPYABLE(
		original
	);
public:
	original(
		sge::window::parameters const &,
		sge::systems::modules::renderer::optional_system_ref const &
	);

	~original();

	sge::window::system &
	system();

	sge::window::object &
	window() const;
private:
	awl::system::object_scoped_ptr const awl_system_;

	awl::system::event::processor_scoped_ptr const awl_system_event_processor_;

	awl::event::processor_scoped_ptr const awl_event_processor_;

	awl::window::instance_shared_ptr const awl_window_;

	awl::window::event::processor_scoped_ptr const awl_window_event_processor_;

	sge::window::system system_;

	sge::window::object_ptr const window_;
};

}
}
}
}

#endif
