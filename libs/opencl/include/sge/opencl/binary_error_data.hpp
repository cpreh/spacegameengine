//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENCL_BINARY_ERROR_DATA_HPP_INCLUDED
#define SGE_OPENCL_BINARY_ERROR_DATA_HPP_INCLUDED

#include <fcppt/config/external_begin.hpp>
#include <boost/range/iterator_range.hpp>
#include <fcppt/config/external_end.hpp>

namespace sge
{
namespace opencl
{
typedef
boost::iterator_range<unsigned char const *>
binary_error_data;
}
}

#endif
