#include "../load_context.hpp"
#include <sge/image/file_exception.hpp>
#include <sge/image/unsupported_format.hpp>
#include <sge/log/headers.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/math/dim/output.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/text.hpp>
#include <climits>
#include <cstddef>

std::size_t const sge::libpng::load_context::header_bytes_ = 
	static_cast<std::size_t>(8);

sge::libpng::load_context::load_context(
	sge::filesystem::path const &_path)
:
	context_base(
		_path),
	file_(
		_path),
	read_ptr_(),
	dim_(),
	bytes_(),
	format_()
{
	if (!file_.is_open())
		throw 
			image::file_exception(
				_path,
				SGE_TEXT("couldn't open file"));

	if (!is_png())
		throw 
			image::unsupported_format(
				_path,
				SGE_TEXT("not a png file")
			);

	read_ptr_.reset(
		new read_ptr(
			png_create_read_struct(
				PNG_LIBPNG_VER_STRING, 
				static_cast<png_voidp>(
					this),
				&load_context::handle_error, 
				&load_context::handle_warning)));

	png_set_sig_bytes(
		read_ptr_->ptr(), 
		static_cast<png_size_t>(
			header_bytes_));
	
	png_set_read_fn(
		read_ptr_->ptr(),
	  this,
		&load_context::handle_read);
	
	png_read_info(
		read_ptr_->ptr(),
		read_ptr_->info());
	
	dim_ = image::dim_type(
		static_cast<image::dim_type::value_type>(
			png_get_image_width(
				read_ptr_->ptr(),
				read_ptr_->info())),
		static_cast<image::dim_type::value_type>(
			png_get_image_height(
				read_ptr_->ptr(),
				read_ptr_->info())));

	png_byte const cs = 
		png_get_channels(
			read_ptr_->ptr(),
			read_ptr_->info());
	png_byte const bpp = 
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	png_uint_32 const color_type = 
		png_get_color_type(
			read_ptr_->ptr(),
			read_ptr_->info());
	SGE_LOG_DEBUG(
		log::global(),
		log::_ << SGE_TEXT("png: dimensions: ") << dim_);
	SGE_LOG_DEBUG(
		log::global(),
		log::_ << SGE_TEXT("png: bit depth: ") << static_cast<int>(bpp));
	SGE_LOG_DEBUG(
		log::global(),
		log::_ << SGE_TEXT("png: channels: ") << static_cast<int>(cs));

	if (color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_palette_to_rgb(
			read_ptr_->ptr());
	}
	else if (color_type == PNG_COLOR_TYPE_GRAY)
	{
		if (bpp < 8)
			png_set_gray_1_2_4_to_8(
				read_ptr_->ptr());
	}

	if (png_get_valid(read_ptr_->ptr(),read_ptr_->info(), PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(
			read_ptr_->ptr());
	
	if (bpp == 16)
		png_set_strip_16(
			read_ptr_->ptr());

	bytes_.reserve(
		static_cast<byte_vector::size_type>(
			dim_.content()*(bpp/CHAR_BIT)*cs));

	typedef container::raw_vector<png_bytep> row_ptr_vector;
	
	row_ptr_vector row_ptrs(
		static_cast<row_ptr_vector::size_type>(
			dim_.h()));
	
	row_ptr_vector::size_type const stride = 
		cs * bpp/CHAR_BIT * dim_.w();

	for (row_ptr_vector::size_type i = 0; i < row_ptrs.size(); ++i)
		row_ptrs[i] = bytes_.data() + i * stride;
	
	png_read_image(
		read_ptr_->ptr(),
		row_ptrs.data());
	
	format_ = convert_format();
}

sge::image::dim_type const &sge::libpng::load_context::dim() const
{
	return dim_;
}

sge::libpng::byte_vector &sge::libpng::load_context::bytes()
{
	return bytes_;
}

sge::libpng::byte_vector const &sge::libpng::load_context::bytes() const
{
	return bytes_;
}

sge::image::color::format::type sge::libpng::load_context::format() const
{
	return format_;
}

bool sge::libpng::load_context::is_png()
{
	char buf[header_bytes_];

	file_.read(
		buf,
		static_cast<std::streamsize>(
			header_bytes_));
	
	if (file_.gcount() < static_cast<std::streamsize>(header_bytes_))
		return false;
	
	return 
		!png_sig_cmp(
			reinterpret_cast<png_byte *>(
				buf),
			static_cast<png_size_t>(
				0),
			static_cast<png_size_t>(
				header_bytes_));
}

void sge::libpng::load_context::handle_read(
	png_structp read_ptr,
	png_bytep data, 
	png_size_t length)
{
	static_cast<load_context *>(png_get_io_ptr(read_ptr))->handle_read_impl(
		data,
		length);
}

void sge::libpng::load_context::handle_read_impl(
	png_bytep _data,
	png_size_t _length)
{
	file_.read(
		reinterpret_cast<char *>(
			_data),
		static_cast<std::streamsize>(
			_length));
	if (file_.gcount() < static_cast<std::streamsize>(_length))
		throw 
			image::file_exception(
				path_,
				SGE_TEXT("didn't read as many bytes as supposed to"));
	if (!file_)
		throw 
			image::file_exception(
				path_,
				SGE_TEXT("reading failed"));
}

sge::image::color::format::type sge::libpng::load_context::convert_format() const
{
	switch(
		png_get_color_type(
			read_ptr_->ptr(),
			read_ptr_->info()))
	{
		case PNG_COLOR_TYPE_GRAY:
			return convert_gray_format();
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			throw image::unsupported_format(path_,SGE_TEXT("gray alpha"));
		break;
		case PNG_COLOR_TYPE_PALETTE:
			throw image::unsupported_format(path_,SGE_TEXT("palette"));
		case PNG_COLOR_TYPE_RGB:
			return convert_rgb_format();
		case PNG_COLOR_TYPE_RGB_ALPHA:
			return convert_rgba_format();
	}
	throw image::unsupported_format(path_,SGE_TEXT("unknown format"));
}

sge::image::color::format::type sge::libpng::load_context::convert_gray_format() const
{
	png_byte const depth = 
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	if (depth != 8)
		throw image::unsupported_format(path_,SGE_TEXT("gray, ")+lexical_cast<string>(depth)+SGE_TEXT(" bits per pixel"));
	return sge::image::color::format::gray8;
}

sge::image::color::format::type sge::libpng::load_context::convert_rgb_format() const
{
	png_byte const depth = 
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	throw image::unsupported_format(path_,SGE_TEXT("rgb, ")+lexical_cast<string>(depth)+SGE_TEXT(" bits"));
}

sge::image::color::format::type sge::libpng::load_context::convert_rgba_format() const
{
	png_byte const depth = 
		png_get_bit_depth(
			read_ptr_->ptr(),
			read_ptr_->info());
	if (depth != 8)
		throw image::unsupported_format(path_,SGE_TEXT("rgb, ")+lexical_cast<string>(depth)+SGE_TEXT(" bits"));
	return sge::image::color::format::rgba8;
}
