#ifndef SGE_IMAGE_COLOR_ANY_FROM_STRING_HPP_INCLUDED
#define SGE_IMAGE_COLOR_ANY_FROM_STRING_HPP_INCLUDED

#include <sge/image/symbol.hpp>
#include <sge/image/color/any/object.hpp>
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
SGE_IMAGE_SYMBOL
sge::image::color::any::object const
from_string(
	std::string const &);

SGE_IMAGE_SYMBOL
sge::image::color::any::object const
from_string(
	std::wstring const &);
}
}
}
}

#endif
