#ifndef SGE_LIBPNG_GENERAL_ERROR_HPP_INCLUDED
#define SGE_LIBPNG_GENERAL_ERROR_HPP_INCLUDED

#include <sge/exception.hpp>

namespace sge
{
namespace libpng
{
class general_error
:
	public sge::exception
{
public:
	general_error(
		sge::string const &);
};
}
}

#endif
