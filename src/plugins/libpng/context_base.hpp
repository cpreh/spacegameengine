#ifndef SGE_LIBPNG_CONTEXT_BASE_HPP_INCLUDED
#define SGE_LIBPNG_CONTEXT_BASE_HPP_INCLUDED

#include <sge/filesystem/path.hpp>
#include <png.h>

namespace sge
{
namespace libpng
{
class context_base
{
protected:
	context_base(
		filesystem::path const &);

	filesystem::path const path_;

	static void handle_warning(
		png_structp,
		png_const_charp);
	void handle_warning_impl(
		png_const_charp);
	static void handle_error(
		png_structp,
		png_const_charp);
	void handle_error_impl(
		png_const_charp);
	
	virtual ~context_base();
};
}
}

#endif
