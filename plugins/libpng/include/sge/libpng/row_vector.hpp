//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_LIBPNG_ROW_VECTOR_HPP_INCLUDED
#define SGE_LIBPNG_ROW_VECTOR_HPP_INCLUDED

#include <sge/libpng/png.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace libpng
{

typedef
std::vector<
	png_bytep
>
row_vector;

}
}

#endif
