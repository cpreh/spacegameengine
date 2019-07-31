//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_VIEW_WRAP_HPP_INCLUDED
#define SGE_IMAGE_VIEW_WRAP_HPP_INCLUDED

#include <sge/image/view/to_wrapped_type.hpp>


namespace sge
{
namespace image
{
namespace view
{

template<
	typename View
>
inline
sge::image::view::to_wrapped_type<
	View
>
wrap(
	View const &_view
)
{
	return
		sge::image::view::to_wrapped_type<
			View
		>(
			_view
		);
}

}
}
}

#endif
