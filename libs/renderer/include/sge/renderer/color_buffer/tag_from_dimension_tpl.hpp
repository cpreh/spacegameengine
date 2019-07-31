//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_COLOR_BUFFER_TAG_FROM_DIMENSION_TPL_HPP_INCLUDED
#define SGE_RENDERER_COLOR_BUFFER_TAG_FROM_DIMENSION_TPL_HPP_INCLUDED

#include <sge/image/size_type.hpp>
#include <sge/image2d/tag.hpp>
#include <sge/image3d/tag.hpp>


namespace sge
{
namespace renderer
{
namespace color_buffer
{

template<
	sge::image::size_type
>
struct tag_from_dimension_tpl;

template<>
struct tag_from_dimension_tpl<
	2u
>
{
	typedef
	sge::image2d::tag
	type;
};

template<>
struct tag_from_dimension_tpl<
	3u
>
{
	typedef
	sge::image3d::tag
	type;
};

}
}
}

#endif
