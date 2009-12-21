#ifndef SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_WRITE_CONTEXT_HPP_INCLUDED

#include "write_ptr.hpp"
#include "context_base.hpp"
#include "byte_vector.hpp"
#include <sge/image/view/const_object.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/dim_type.hpp>
#include <fcppt/filesystem/path.hpp>
#include <fcppt/io/ofstream.hpp>
#include <png.h>

namespace sge
{
namespace libpng
{
class write_context
:
	public context_base
{
public:
	write_context(
		fcppt::filesystem::path const &,
		image::dim_type const &,
		byte_vector &,
		image::color::format::type);
private:
	fcppt::io::ofstream file_;
	byte_vector &bytes_;
	image::color::format::type const format_;
	write_ptr const write_ptr_;

	static void handle_write(
		png_structp,
		png_bytep,
		png_size_t);
	void handle_write_impl(
		png_bytep,
		png_size_t);
	static void handle_flush(
		png_structp);
	void handle_flush_impl();

};
}
}

#endif
