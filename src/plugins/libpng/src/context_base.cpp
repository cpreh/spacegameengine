#include "../context_base.hpp"
#include <sge/image/file_exception.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>

sge::libpng::context_base::context_base(
	filesystem::path const &_path)
:
	path_(
		_path)
{
}

void sge::libpng::context_base::handle_warning(
	png_structp read_ptr,
	png_const_charp data)
{
	static_cast<context_base *>(png_get_io_ptr(read_ptr))->handle_warning_impl(
		data);
}

void sge::libpng::context_base::handle_warning_impl(
	png_const_charp const message)
{
	SGE_LOG_WARNING(
		log::global(),
		log::_ 
			<< SGE_TEXT("libpng: file: ") 
			<< path_.string() 
			<< SGE_TEXT(": ") 
			<< iconv(message));
}

void sge::libpng::context_base::handle_error(
	png_structp read_ptr,
	png_const_charp data)
{
	static_cast<context_base *>(png_get_io_ptr(read_ptr))->handle_error_impl(
		data);
}

void sge::libpng::context_base::handle_error_impl(
	png_const_charp const message)
{
	throw 
		image::file_exception(
			path_,
			iconv(
				message));
}

sge::libpng::context_base::~context_base() {}
