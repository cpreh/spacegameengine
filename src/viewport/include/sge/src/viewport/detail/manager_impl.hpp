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


#ifndef SGE_SRC_VIEWPORT_DETAIL_MANAGER_IMPL_HPP_INCLUDED
#define SGE_SRC_VIEWPORT_DETAIL_MANAGER_IMPL_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/target_base_fwd.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/resize_function.hpp>
#include <sge/viewport/detail/manager_impl_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/window/event/resize_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sge
{
namespace viewport
{
namespace detail
{

class manager_impl
{
	FCPPT_NONCOPYABLE(
		manager_impl
	);
public:
	manager_impl(
		sge::renderer::device &,
		sge::window::object &,
		sge::viewport::resize_function const &
	);

	~manager_impl();

	fcppt::signal::auto_connection
	manage_callback(
		viewport::manage_callback const &
	);
private:
	void
	on_resize(
		awl::window::event::resize const &
	);

	sge::renderer::target_base &target_;

	viewport::resize_function const resize_function_;

	fcppt::signal::scoped_connection const resize_connection_;

	typedef fcppt::signal::object<
		viewport::manage_function
	> manage_signal;

	manage_signal manage_signal_;
};

}
}
}

#endif
