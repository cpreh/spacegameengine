#ifndef SGE_LIBPNG_EXCEPTION_HPP_INCLUDED
#define SGE_LIBPNG_EXCEPTION_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/filesystem/path.hpp>

namespace sge
{
namespace libpng
{
class exception
:
	public sge::exception
{
public:
	exception(
		sge::string const &);
};
}
}

#endif
