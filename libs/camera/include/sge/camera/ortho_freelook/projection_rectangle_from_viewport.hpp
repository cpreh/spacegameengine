//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CAMERA_ORTHO_FREELOOK_PROJECTION_RECTANGLE_FROM_VIEWPORT_HPP_INCLUDED
#define SGE_CAMERA_ORTHO_FREELOOK_PROJECTION_RECTANGLE_FROM_VIEWPORT_HPP_INCLUDED

#include <sge/camera/detail/symbol.hpp>
#include <sge/camera/ortho_freelook/object_fwd.hpp>
#include <sge/renderer/target/viewport_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sge
{
namespace camera
{
namespace ortho_freelook
{
class projection_rectangle_from_viewport
{
FCPPT_NONCOPYABLE(
	projection_rectangle_from_viewport);
public:
	SGE_CAMERA_DETAIL_SYMBOL
	projection_rectangle_from_viewport(
		sge::camera::ortho_freelook::object &,
		sge::viewport::manager &);

	SGE_CAMERA_DETAIL_SYMBOL
	~projection_rectangle_from_viewport();
private:
	sge::camera::ortho_freelook::object &camera_;
	fcppt::signal::auto_connection viewport_callback_connection_;

	void
	viewport_callback(
		sge::renderer::target::viewport const &);
};
}
}
}

#endif
