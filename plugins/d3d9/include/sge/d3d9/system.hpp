//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_D3D9_SYSTEM_HPP_INCLUDED
#define SGE_D3D9_SYSTEM_HPP_INCLUDED

#include <sge/d3d9/d3d_unique_ptr.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/system.hpp>
#include <sge/renderer/device/core_unique_ptr.hpp>
#include <sge/renderer/device/ffp_unique_ptr.hpp>
#include <sge/renderer/device/parameters_fwd.hpp>
#include <sge/renderer/pixel_format/object_fwd.hpp>
#include <awl/visual/object_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace d3d9
{

class system
:
	public sge::renderer::system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		fcppt::log::object &
	);

	~system()
	override;
private:
	sge::renderer::device::core_unique_ptr
	create_core_renderer(
		sge::renderer::device::parameters const &
	)
	override;

	sge::renderer::device::ffp_unique_ptr
	create_ffp_renderer(
		sge::renderer::device::parameters const &
	)
	override;

	awl::visual::object_unique_ptr
	create_visual(
		sge::renderer::pixel_format::object const &
	)
	override;

	fcppt::log::object &log_;

	sge::d3d9::d3d_unique_ptr const system_;
};

}
}

#endif
