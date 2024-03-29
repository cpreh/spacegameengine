//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_OPENCL_BINARY_ERROR_DATA_HPP_INCLUDED
#define SGE_OPENCL_BINARY_ERROR_DATA_HPP_INCLUDED

#include <fcppt/iterator/range_impl.hpp>

namespace sge::opencl
{

using binary_error_data = fcppt::iterator::range<unsigned char const *>;

}

#endif
