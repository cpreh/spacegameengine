//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/file_exception.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/write_context.hpp>
#include <sge/libpng/write_ptr.hpp>
#include <sge/media/optional_name.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/from_void_ptr.hpp>
#include <fcppt/cast/to_char_ptr.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/config/external_begin.hpp>
#include <ostream>
#include <fcppt/config/external_end.hpp>


sge::libpng::write_context::write_context(
	sge::media::optional_name const &_name,
	std::ostream &_stream,
	sge::libpng::write_ptr const &_write_ptr
)
:
	name_(
		_name
	),
	stream_(
		_stream
	)
{
	::png_set_write_fn(
		_write_ptr.ptr(),
		this,
		&sge::libpng::write_context::handle_write,
		&sge::libpng::write_context::handle_flush
	);
}

sge::libpng::write_context::~write_context()
{
}

void
sge::libpng::write_context::handle_write(
	png_structp const _ptr,
	png_bytep const _data,
	png_size_t const _length
)
{
	sge::libpng::write_context::get_instance(
		_ptr
	).handle_write_impl(
		_data,
		_length
	);
}

void
sge::libpng::write_context::handle_write_impl(
	png_bytep const _data,
	png_size_t const _length
)
{
	stream_.write(
		fcppt::cast::to_char_ptr<
			char const *
		>(
			_data
		),
		fcppt::cast::to_signed(
			_length
		)
	);

	if(
		!stream_
	)
		throw
			sge::image2d::file_exception(
				name_,
				FCPPT_TEXT("error writing")
			);
}

void
sge::libpng::write_context::handle_flush(
	png_structp const _ptr
)
{
	sge::libpng::write_context::get_instance(
		_ptr
	).handle_flush_impl();
}

void
sge::libpng::write_context::handle_flush_impl()
{
	stream_.flush();
}

sge::libpng::write_context &
sge::libpng::write_context::get_instance(
	png_structp const _ptr
)
{
	return
		*fcppt::cast::from_void_ptr<
			sge::libpng::write_context *
		>(
			::png_get_io_ptr(
				_ptr
			)
		);
}
