#ifndef SGE_SCENIC_RENDER_CONTEXT_EMISSIVE_COLOR_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_EMISSIVE_COLOR_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
FCPPT_MAKE_STRONG_TYPEDEF(
	sge::image::color::any::object,
	emissive_color);
}
}
}

#endif
