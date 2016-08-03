/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_IMPL_WINDOW_OBJECT_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_WINDOW_OBJECT_HPP_INCLUDED

#include <sge/systems/window_fwd.hpp>
#include <sge/systems/impl/renderer/optional_system_ref.hpp>
#include <sge/systems/impl/window/base_unique_ptr.hpp>
#include <sge/systems/impl/window/object_fwd.hpp>
#include <sge/systems/impl/window/quit_fwd.hpp>
#include <sge/systems/impl/window/system_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace systems
{
namespace impl
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
		sge::systems::impl::window::system const &,
		sge::systems::impl::renderer::optional_system_ref const &
	);

	~object();

	sge::window::object &
	get() const;

	void
	post_init();
private:
	sge::systems::impl::window::base_unique_ptr const base_;

	bool const show_on_post_;

	typedef
	fcppt::unique_ptr<
		sge::systems::impl::window::quit
	>
	quit_unique_ptr;

	typedef
	fcppt::optional::object<
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
