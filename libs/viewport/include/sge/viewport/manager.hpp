//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_VIEWPORT_MANAGER_HPP_INCLUDED
#define SGE_VIEWPORT_MANAGER_HPP_INCLUDED

#include <sge/core/detail/class_symbol.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manage_callback.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/viewport/optional_resize_callback_fwd.hpp>
#include <sge/viewport/detail/manager_impl_fwd.hpp>
#include <sge/viewport/detail/symbol.hpp>
#include <sge/window/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sge
{
namespace viewport
{

class SGE_CORE_DETAIL_CLASS_SYMBOL manager
{
	FCPPT_NONCOPYABLE(
		manager
	);
public:
	SGE_VIEWPORT_DETAIL_SYMBOL
	manager(
		sge::renderer::device::core &,
		sge::window::object &,
		sge::viewport::optional_resize_callback const &
	);

	SGE_VIEWPORT_DETAIL_SYMBOL
	~manager();

	SGE_VIEWPORT_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	manage_callback(
		sge::viewport::manage_callback const &
	);

	SGE_VIEWPORT_DETAIL_SYMBOL
	void
	resize_callback(
		sge::viewport::optional_resize_callback const &
	);

	SGE_VIEWPORT_DETAIL_SYMBOL
	sge::renderer::target::viewport
	viewport() const;
private:
	typedef
	fcppt::unique_ptr<
		sge::viewport::detail::manager_impl
	>
	impl_ptr;

	impl_ptr const impl_;
};

}
}

#endif
