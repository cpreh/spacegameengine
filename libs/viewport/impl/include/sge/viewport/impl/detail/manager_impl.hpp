//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VIEWPORT_IMPL_DETAIL_MANAGER_IMPL_HPP_INCLUDED
#define SGE_VIEWPORT_IMPL_DETAIL_MANAGER_IMPL_HPP_INCLUDED

#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/target/base_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/optional_resize_callback.hpp>
#include <sge/viewport/detail/manager_impl_fwd.hpp>
#include <sge/window/object_ref.hpp>
#include <awl/event/container.hpp>
#include <awl/window/event/base_fwd.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_decl.hpp>


namespace sge::viewport::detail
{

class manager_impl
{
	FCPPT_NONMOVABLE(
		manager_impl
	);
public:
	manager_impl(
		sge::renderer::device::core_ref,
		sge::window::object_ref,
		sge::viewport::optional_resize_callback &&
	);

	~manager_impl();

	[[nodiscard]]
	fcppt::signal::auto_connection
	manage_callback(
		sge::viewport::manage_callback &&
	);

	void
	resize_callback(
		sge::viewport::optional_resize_callback &&
	);

	[[nodiscard]]
	sge::renderer::target::viewport
	viewport() const;
private:
	[[nodiscard]]
	awl::event::container
	on_resize(
		awl::window::event::base const &
	);

	sge::renderer::target::base &target_;

	sge::viewport::optional_resize_callback resize_callback_;

	fcppt::signal::auto_connection const event_connection_;

	using
	manage_signal
	=
	fcppt::signal::object<
		sge::viewport::manage_function
	>;

	manage_signal manage_signal_;
};

}

#endif
