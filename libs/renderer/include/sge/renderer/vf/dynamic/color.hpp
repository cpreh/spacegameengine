//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VF_DYNAMIC_COLOR_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_COLOR_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/renderer/detail/symbol.hpp>
#include <sge/renderer/vf/dynamic/color_fwd.hpp>


namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class color
{
public:
	SGE_RENDERER_DETAIL_SYMBOL
	explicit
	color(
		sge::image::color::format
	);

	[[nodiscard]]
	SGE_RENDERER_DETAIL_SYMBOL
	sge::image::color::format
	color_format() const;
private:
	sge::image::color::format color_format_;
};

SGE_RENDERER_DETAIL_SYMBOL
bool
operator==(
	sge::renderer::vf::dynamic::color const &,
	sge::renderer::vf::dynamic::color const &
);

}
}
}
}

#endif
