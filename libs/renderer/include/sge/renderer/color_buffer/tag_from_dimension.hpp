//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_COLOR_BUFFER_TAG_FROM_DIMENSION_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_TAG_FROM_DIMENSION_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/renderer/color_buffer/tag_from_dimension_tpl.hpp>


namespace sge
{
namespace renderer
{
namespace color_buffer
{

template<
	sge::image::size_type Dim
>
using
tag_from_dimension
=
typename
sge::renderer::color_buffer::tag_from_dimension_tpl<
	Dim
>::type;

}
}
}

#endif
