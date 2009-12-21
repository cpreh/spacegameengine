#include "../context_base.hpp"
#include <sge/image/file_exception.hpp>
#include <sge/log/global.hpp>
#include <fcppt/iconv.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/headers.hpp>

sge::libpng::context_base::context_base(
	fcppt::filesystem::path const &_path
)
:
	path_(
		_path
	)
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
	FCPPT_LOG_WARNING(
		log::global(),
		fcppt::log::_
			<< FCPPT_TEXT("libpng: file: ")
			<< path_.string()
			<< FCPPT_TEXT(": ")
			<< fcppt::iconv(message)
	);
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
			fcppt::iconv(
				message
			)
		);
}

sge::libpng::context_base::~context_base() {}
