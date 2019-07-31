//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_TRAITS_DIMENSION_HPP_INCLUDED
#define SGE_RENDERER_INDEX_TRAITS_DIMENSION_HPP_INCLUDED

#include <sge/image/dimension_integral_c.hpp>
#include <sge/image/traits/image/dimension_tpl_fwd.hpp>
#include <sge/renderer/index/tag.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace image
{

template<>
struct dimension_tpl<
	sge::renderer::index::tag
>
{
	typedef
	sge::image::dimension_integral_c<
		1
	>
	type;
};

}
}
}
}

#endif
