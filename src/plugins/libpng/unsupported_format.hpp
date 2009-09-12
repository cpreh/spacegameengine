#ifndef SGE_LIBPNG_UNSUPPORTED_FORMAT_HPP_INCLUDED
#define SGE_LIBPNG_UNSUPPORTED_FORMAT_HPP_INCLUDED

#include "file_exception.hpp"

namespace sge
{
namespace libpng
{
class unsupported_format
:
	public file_exception
{
public:
	unsupported_format(
		filesystem::path const &,
		sge::string const &);
};
}
}

#endif
