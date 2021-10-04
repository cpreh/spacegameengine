//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SYSTEMS_IMPL_RENDERER_DEVICE_HPP_INCLUDED
#define SGE_SYSTEMS_IMPL_RENDERER_DEVICE_HPP_INCLUDED

#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/systems/detail/renderer_fwd.hpp>
#include <sge/systems/impl/renderer/device_fwd.hpp>
#include <sge/systems/impl/renderer/system_fwd.hpp>
#include <sge/systems/impl/window/object_fwd.hpp>
#include <sge/viewport/manager.hpp>
#include <fcppt/nonmovable.hpp>


namespace sge::systems::impl::renderer
{

class device
{
	FCPPT_NONMOVABLE(
		device
	);
public:
	device(
		sge::systems::detail::renderer const &,
		sge::systems::impl::renderer::system const &,
		sge::systems::impl::window::object const &
	);

	~device();

	[[nodiscard]]
	sge::renderer::device::ffp &
	get_ffp() const;

	[[nodiscard]]
	sge::renderer::device::core &
	get_core() const;

	[[nodiscard]]
	sge::viewport::manager &
	viewport_manager();
private:
	sge::renderer::device::core_unique_ptr const renderer_device_;

	sge::viewport::manager viewport_manager_;
};

}

#endif
