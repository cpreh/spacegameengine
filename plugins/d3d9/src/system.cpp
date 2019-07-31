//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/d3d9/create.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/device.hpp>
#include <sge/d3d9/system.hpp>
#include <sge/d3d9/visual.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/visual/object.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/log/object_fwd.hpp>


sge::d3d9::system::system(
	fcppt::log::object &_log
)
:
	sge::renderer::system(),
	log_{
		_log
	},
	system_{
		sge::d3d9::create()
	}
{
}

sge::d3d9::system::~system()
{
}

sge::renderer::device::core_unique_ptr
sge::d3d9::system::create_core_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::device::core
		>(
			this->create_ffp_renderer(
				_parameters
			)
		);
}

sge::renderer::device::ffp_unique_ptr
sge::d3d9::system::create_ffp_renderer(
	sge::renderer::device::parameters const &_parameters
)
{
	return
		fcppt::unique_ptr_to_base<
			sge::renderer::device::ffp
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::device
			>(
				*system_,
				log_,
				_parameters
			)
		);
}

awl::visual::object_unique_ptr
sge::d3d9::system::create_visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
{
	return
		fcppt::unique_ptr_to_base<
			awl::visual::object
		>(
			fcppt::make_unique_ptr<
				sge::d3d9::visual
			>(
				_pixel_format
			)
		);
}
