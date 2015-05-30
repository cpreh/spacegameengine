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


#ifndef SGE_SRC_SYSTEMS_MODULES_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/src/systems/modules/renderer/optional_system_ref.hpp>
#include <sge/src/systems/modules/window/base_unique_ptr.hpp>
#include <sge/src/systems/modules/window/object_fwd.hpp>
#include <sge/src/systems/modules/window/quit_fwd.hpp>
#include <sge/src/systems/modules/window/system_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/unique_ptr_decl.hpp>


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
		sge::systems::modules::window::system const &,
		sge::systems::modules::renderer::optional_system_ref const &
	);

	~object();

	sge::window::object &
	get() const;

	void
	post_init();
private:
	sge::systems::modules::window::base_unique_ptr const base_;

	bool const show_on_post_;

	typedef
	fcppt::unique_ptr<
		sge::systems::modules::window::quit
	>
	quit_unique_ptr;

	typedef
	fcppt::optional<
		quit_unique_ptr
	>
	optional_quit_unique_ptr;

	optional_quit_unique_ptr const quit_;
};

}
}
}
}

#endif
