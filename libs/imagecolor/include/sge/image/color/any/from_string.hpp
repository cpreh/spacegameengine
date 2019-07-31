//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_ANY_FROM_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ANY_FROM_STRING_HPP_INCLUDED

#include <sge/image/color/any/object.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <string>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace image
{
namespace color
{
namespace any
{

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::any::object
from_string(
	std::string const &
);

SGE_IMAGE_COLOR_DETAIL_SYMBOL
sge::image::color::any::object
from_string(
	std::wstring const &
);

}
}
}
}

#endif
