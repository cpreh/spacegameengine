#ifndef SGE_LIBPNG_NOT_PNG_HPP_INCLUDED
#define SGE_LIBPNG_NOT_PNG_HPP_INCLUDED

#include <sge/exception.hpp>
#include <sge/filesystem/path.hpp>

namespace sge
{
namespace libpng
{
class not_png
:
	public sge::exception
{
public:
	not_png(
		sge::filesystem::path const &);
};
}
}

#endif
