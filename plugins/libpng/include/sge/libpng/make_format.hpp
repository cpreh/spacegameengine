//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_MAKE_FORMAT_HPP_INCLUDED
#define SGE_LIBPNG_MAKE_FORMAT_HPP_INCLUDED

#include <sge/libpng/gamma.hpp>
#include <sge/libpng/optional_format.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace libpng
{

sge::libpng::optional_format
make_format(
	fcppt::log::object &,
	png_byte color_type,
	png_byte bit_depth,
	sge::libpng::gamma
);

}
}

#endif
