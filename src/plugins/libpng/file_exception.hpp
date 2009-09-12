#ifndef SGE_LIBPNG_FILE_EXCEPTION_HPP_INCLUDED
#define SGE_LIBPNG_FILE_EXCEPTION_HPP_INCLUDED

#include "exception.hpp"
#include <sge/filesystem/path.hpp>

namespace sge
{
namespace libpng
{
class file_exception
:
	public exception
{
public:
	file_exception(
		filesystem::path const &,
		sge::string const &);
};
}
}

#endif
