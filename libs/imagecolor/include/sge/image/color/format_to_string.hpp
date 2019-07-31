//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_IMAGE_COLOR_FORMAT_TO_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_FORMAT_TO_STRING_HPP_INCLUDED

#include <sge/image/color/format_fwd.hpp>
#include <sge/image/color/detail/symbol.hpp>
#include <fcppt/string.hpp>


namespace sge
{
namespace image
{
namespace color
{

SGE_IMAGE_COLOR_DETAIL_SYMBOL
fcppt::string
format_to_string(
	sge::image::color::format
);

}
}
}

#endif
