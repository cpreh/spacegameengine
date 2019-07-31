//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SCENIC_GRID_OBJECT_HPP_INCLUDED
#define SGE_SCENIC_GRID_OBJECT_HPP_INCLUDED

#include <sge/camera/base_fwd.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/line_drawer/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/scenic/detail/symbol.hpp>
#include <sge/scenic/grid/depth_test.hpp>
#include <sge/scenic/grid/distance_to_origin.hpp>
#include <sge/scenic/grid/orientation_fwd.hpp>
#include <sge/scenic/grid/rect.hpp>
#include <sge/scenic/grid/spacing.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace grid
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_SCENIC_DETAIL_SYMBOL
	object(
		sge::renderer::device::ffp &,
		sge::camera::base const &,
		sge::scenic::grid::orientation,
		sge::scenic::grid::rect const &,
		sge::scenic::grid::spacing const &,
		sge::scenic::grid::distance_to_origin const &,
		sge::image::color::any::object const &);

	SGE_SCENIC_DETAIL_SYMBOL
	void
	render(
		sge::renderer::context::ffp &,
		sge::scenic::grid::depth_test const &);

	SGE_SCENIC_DETAIL_SYMBOL
	~object();
private:
	sge::renderer::device::ffp &renderer_;
	sge::camera::base const &camera_;
	sge::line_drawer::object line_drawer_;
};
}
}
}

#endif
