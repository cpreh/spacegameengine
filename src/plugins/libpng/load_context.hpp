#ifndef SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED
#define SGE_LIBPNG_LOAD_CONTEXT_HPP_INCLUDED

#include "context_base.hpp"
#include "read_ptr.hpp"
#include "byte_vector.hpp"
#include <sge/filesystem/path.hpp>
#include <sge/image/dim_type.hpp>
#include <sge/math/dim/basic_decl.hpp>
#include <sge/image/color/format.hpp>
#include <sge/scoped_ptr.hpp>
#include <boost/filesystem/fstream.hpp>
#include <png.h>
#include <cstddef>

namespace sge
{
namespace libpng
{
class load_context
:
	public context_base
{
public:
	explicit load_context(
		sge::filesystem::path const &);
	image::dim_type const &dim() const;
	byte_vector &bytes();
	byte_vector const &bytes() const;
	image::color::format::type format() const;
private:
	static std::size_t const header_bytes_;

	boost::filesystem::ifstream file_;
	scoped_ptr<read_ptr> read_ptr_;
	image::dim_type dim_;
	byte_vector bytes_;
	image::color::format::type format_;

	bool is_png();
	static void handle_read(
		png_structp,
		png_bytep data,
		png_size_t length);
	void handle_read_impl(
		png_bytep data,
		png_size_t length);
	sge::image::color::format::type convert_format() const;
	sge::image::color::format::type convert_gray_format() const;
	sge::image::color::format::type convert_rgb_format() const;
	sge::image::color::format::type convert_rgba_format() const;
};
}
}

#endif
