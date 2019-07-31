//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_TO_SGE_FORMAT_HPP_INCLUDED
#define SGE_LIBPNG_TO_SGE_FORMAT_HPP_INCLUDED

#include <sge/image/color/format.hpp>
#include <sge/libpng/format_fwd.hpp>


namespace sge
{
namespace libpng
{

sge::image::color::format
to_sge_format(
	sge::libpng::format
);

}
}

#endif
