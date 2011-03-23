#ifndef SGE_LINE_DRAWER_LINE_HPP_INCLUDED
#define SGE_LINE_DRAWER_LINE_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/image/colors.hpp>
#include <sge/line_drawer/color_format.hpp>
#include <sge/line_drawer/symbol.hpp>
#include <sge/line_drawer/color.hpp>
#include <sge/renderer/vector3.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/variant/object.hpp>

namespace sge
{
namespace line_drawer
{
class line
{
public:
	SGE_LINE_DRAWER_SYMBOL explicit
	line(
		sge::renderer::vector3 const &,
		sge::renderer::vector3 const &,
		sge::image::color::any::object const & = sge::image::colors::white(),
		sge::image::color::any::object const & = sge::image::colors::white());

	SGE_LINE_DRAWER_SYMBOL sge::renderer::vector3 const &
	begin() const;

	SGE_LINE_DRAWER_SYMBOL sge::renderer::vector3 const &
	end() const;

	SGE_LINE_DRAWER_SYMBOL color const &
	begin_color() const;

	SGE_LINE_DRAWER_SYMBOL color const &
	end_color() const;
private:
	sge::renderer::vector3 begin_,end_;
	color begin_color_,end_color_;
};
}
}

#endif
