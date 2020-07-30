//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_HEADER_BYTES_HPP_INCLUDED
#define SGE_LIBPNG_HEADER_BYTES_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

using
header_bytes
=
std::integral_constant<
	std::size_t,
	8U // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
>;

}
}

#endif
