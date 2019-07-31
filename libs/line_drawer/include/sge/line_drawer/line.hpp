//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LINE_DRAWER_LINE_HPP_INCLUDED
#define SGE_LINE_DRAWER_LINE_HPP_INCLUDED

#include <sge/image/color/any/object_fwd.hpp>
#include <sge/line_drawer/color.hpp>
#include <sge/line_drawer/color_format.hpp>
#include <sge/line_drawer/detail/symbol.hpp>
#include <sge/renderer/vector3.hpp>


namespace sge
{
namespace line_drawer
{

class line
{
public:
	SGE_LINE_DRAWER_DETAIL_SYMBOL
	line(
		sge::renderer::vector3 const &,
		sge::renderer::vector3 const &
	);

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	line(
		sge::renderer::vector3 const &,
		sge::renderer::vector3 const &,
		sge::image::color::any::object const &,
		sge::image::color::any::object const &
	);

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	sge::renderer::vector3 const &
	begin() const;

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	sge::renderer::vector3 const &
	end() const;

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	sge::line_drawer::color const &
	begin_color() const;

	SGE_LINE_DRAWER_DETAIL_SYMBOL
	sge::line_drawer::color const &
	end_color() const;
private:
	sge::renderer::vector3 begin_,end_;

	sge::line_drawer::color begin_color_,end_color_;
};

}
}

#endif
