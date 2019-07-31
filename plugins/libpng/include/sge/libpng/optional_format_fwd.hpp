//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_OPTIONAL_FORMAT_FWD_HPP_INCLUDED
#define SGE_LIBPNG_OPTIONAL_FORMAT_FWD_HPP_INCLUDED

#include <sge/libpng/format_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace libpng
{

typedef
fcppt::optional::object<
	sge::libpng::format
>
optional_format;

}
}

#endif
