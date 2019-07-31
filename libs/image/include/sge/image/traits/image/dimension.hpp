//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_TRAITS_IMAGE_DIMENSION_HPP_INCLUDED
#define SGE_IMAGE_TRAITS_IMAGE_DIMENSION_HPP_INCLUDED

#include <sge/image/traits/image/dimension_tpl_fwd.hpp>


namespace sge
{
namespace image
{
namespace traits
{
namespace image
{

template<
	typename Tag
>
using
dimension
=
typename
sge::image::traits::image::dimension_tpl<
	Tag
>::type;

}
}
}
}

#endif
