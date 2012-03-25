#ifndef SGE_CAMERA_PERSPECTIVE_PROJECTION_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_CAMERA_PERSPECTIVE_PROJECTION_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/camera/has_mutable_projection_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/camera/symbol.hpp>
#include <sge/renderer/projection/near.hpp>
#include <sge/renderer/projection/far.hpp>
#include <sge/renderer/projection/fov.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>

namespace sge
{
namespace camera
{
class perspective_projection_from_viewport
{
FCPPT_NONCOPYABLE(
	perspective_projection_from_viewport);
public:
	SGE_CAMERA_SYMBOL
	explicit
	perspective_projection_from_viewport(
		sge::camera::has_mutable_projection &,
		sge::renderer::device &,
		sge::viewport::manager &,
		sge::renderer::projection::near const &,
		sge::renderer::projection::far const &,
		sge::renderer::projection::fov const &);

	SGE_CAMERA_SYMBOL
	~perspective_projection_from_viewport();
private:
	sge::camera::has_mutable_projection &camera_;
	sge::renderer::device &renderer_;
	sge::renderer::projection::near near_;
	sge::renderer::projection::far far_;
	sge::renderer::projection::fov fov_;
	fcppt::signal::scoped_connection viewport_callback_connection_;

	void
	viewport_callback();
};
}
}

#endif

