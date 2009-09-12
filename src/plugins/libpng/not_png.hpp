#ifndef SGE_LIBPNG_NOT_PNG_HPP_INCLUDED
#define SGE_LIBPNG_NOT_PNG_HPP_INCLUDED

#include "file_exception.hpp"

namespace sge
{
namespace libpng
{
class not_png
:
	public file_exception
{
public:
	not_png(
		sge::filesystem::path const &);
};
}
}

#endif
