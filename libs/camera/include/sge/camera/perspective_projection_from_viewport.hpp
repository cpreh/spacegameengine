//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_PERSPECTIVE_PROJECTION_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_CAMERA_PERSPECTIVE_PROJECTION_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/camera/has_mutable_projection_fwd.hpp>
#include <sge/camera/detail/symbol.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace camera
{

class perspective_projection_from_viewport
{
	FCPPT_NONCOPYABLE(
		perspective_projection_from_viewport
	);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	perspective_projection_from_viewport(
		sge::camera::has_mutable_projection &,
		sge::viewport::manager &,
		sge::renderer::projection::near,
		sge::renderer::projection::far,
		sge::renderer::projection::fov
	);

	SGE_CAMERA_DETAIL_SYMBOL
	~perspective_projection_from_viewport();
private:
	sge::camera::has_mutable_projection &camera_;

	sge::renderer::projection::near const near_;

	sge::renderer::projection::far const far_;

	sge::renderer::projection::fov const fov_;

	fcppt::signal::auto_connection const viewport_callback_connection_;

	void
	viewport_callback(
		sge::renderer::target::viewport const &
	);
};

}
}

#endif
