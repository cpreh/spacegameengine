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


#ifndef SGE_SRC_SYSTEMS_MODULES_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/window/base_scoped_ptr.hpp>
#include <sge/src/systems/modules/window/object_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <awl/mainloop/dispatcher_fwd.hpp>
#include <awl/mainloop/dispatcher_scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace window
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::systems::window const &,
		sge::systems::modules::renderer::optional_system_ref const &
	);

	~object();

	sge::window::system &
	system() const;

	sge::window::object &
	window() const;

	awl::mainloop::dispatcher &
	awl_dispatcher() const;

	void
	post_init();
private:
	sge::systems::modules::window::base_scoped_ptr base_;

	awl::mainloop::dispatcher_scoped_ptr const dispatcher_;

	bool const show_on_post_;
};

}
}
}
}

#endif
