#ifndef SGE_LIBPNG_BYTE_VECTOR_HPP_INCLUDED
#define SGE_LIBPNG_BYTE_VECTOR_HPP_INCLUDED

#include <fcppt/container/raw_vector.hpp>
#include <png.h>

namespace sge
{
namespace libpng
{
typedef container::raw_vector<png_byte> byte_vector;
}
}

#endif
