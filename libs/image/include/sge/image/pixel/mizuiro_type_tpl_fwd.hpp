//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_PIXEL_MIZUIRO_TYPE_TPL_FWD_HPP_INCLUDED
#define SGE_IMAGE_PIXEL_MIZUIRO_TYPE_TPL_FWD_HPP_INCLUDED

#include <sge/image/pixel/mizuiro_type_fwd.hpp>


namespace sge
{
namespace image
{
namespace pixel
{

template<
	typename Format
>
struct mizuiro_type_tpl
{
	typedef
	sge::image::pixel::mizuiro_type<
		Format
	>
	type;
};

}
}
}

#endif
