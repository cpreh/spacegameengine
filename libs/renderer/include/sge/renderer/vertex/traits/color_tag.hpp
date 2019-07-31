//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_VERTEX_TRAITS_COLOR_TAG_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_TRAITS_COLOR_TAG_HPP_INCLUDED

#include <sge/image/traits/image/color_tag_tpl_fwd.hpp>
#include <sge/renderer/vertex/tag.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace image
{

template<>
struct color_tag_tpl<
	sge::renderer::vertex::tag
>
{
	typedef
	sge::renderer::vertex::tag
	type;
};

}
}
}
}

#endif
