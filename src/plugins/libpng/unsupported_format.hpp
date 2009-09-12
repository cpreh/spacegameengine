#ifndef SGE_LIBPNG_UNSUPPORTED_FORMAT_HPP_INCLUDED
#define SGE_LIBPNG_UNSUPPORTED_FORMAT_HPP_INCLUDED

#include <sge/exception.hpp>

namespace sge
{
namespace libpng
{
class unsupported_format
:
	public sge::exception
{
public:
	unsupported_format(
		sge::string const &);
};
}
}

#endif
