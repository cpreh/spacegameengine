#ifndef SGE_OPENCL_BINARY_ERROR_DATA_HPP_INCLUDED
#define SGE_OPENCL_BINARY_ERROR_DATA_HPP_INCLUDED

#include <boost/range/iterator_range.hpp>

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
