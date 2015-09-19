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


#ifndef SGE_SRC_VIEWPORT_DETAIL_MANAGER_IMPL_HPP_INCLUDED
#define SGE_SRC_VIEWPORT_DETAIL_MANAGER_IMPL_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/viewport/detail/manager_impl_fwd.hpp>
#include <sge/window/object_fwd.hpp>
#include <awl/window/event/resize_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>


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
		sge::renderer::device::core &,
		sge::window::object &,
		sge::viewport::optional_resize_callback const &
	);

	~manager_impl();

	fcppt::signal::auto_connection
	manage_callback(
		sge::viewport::manage_callback const &
	);

	void
	resize_callback(
		sge::viewport::optional_resize_callback const &
	);

	sge::renderer::target::viewport const
	viewport() const;
private:
	void
	on_resize(
		awl::window::event::resize const &
	);

	sge::renderer::target::base &target_;

	sge::viewport::optional_resize_callback resize_callback_;

	fcppt::signal::auto_connection const resize_connection_;

	typedef
	fcppt::signal::object<
		sge::viewport::manage_function
	>
	manage_signal;

	manage_signal manage_signal_;
};

}
}
}

#endif
