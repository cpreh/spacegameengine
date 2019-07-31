//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/file_exception.hpp>
#include <sge/libpng/load_context.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ios>
#include <istream>
#include <fcppt/config/external_end.hpp>


sge::libpng::load_context::load_context(
	std::istream &_stream,
	sge::media::optional_name const &_name,
	sge::libpng::read_ptr const &_read_ptr
)
:
	stream_(
		_stream
	),
	name_(
		_name
	)
{
	::png_set_read_fn(
		_read_ptr.ptr(),
		this,
		&sge::libpng::load_context::handle_read
	);
}

sge::libpng::load_context::~load_context()
{
}

void
sge::libpng::load_context::handle_read(
	png_structp const _read_ptr,
	png_bytep const _data,
	png_size_t const _length
)
{
	fcppt::cast::from_void_ptr<
		sge::libpng::load_context *
	>(
		::png_get_io_ptr(
			_read_ptr
		)
	)->handle_read_impl(
		_data,
		_length
	);
}

void
sge::libpng::load_context::handle_read_impl(
	png_bytep const _data,
	png_size_t const _length
)
{
	std::streamsize const signed_length(
		fcppt::cast::to_signed(
			_length
		)
	);

	if(
		!stream_.read(
			fcppt::cast::to_char_ptr<
				char *
			>(
				_data
			),
			signed_length
		)
	)
		throw
			sge::image2d::file_exception(
				name_,
				FCPPT_TEXT("reading failed")
			);

	if(
		stream_.gcount()
		<
		signed_length
	)
		throw
			sge::image2d::file_exception(
				name_,
				FCPPT_TEXT("didn't read as many bytes as supposed to")
			);
}
