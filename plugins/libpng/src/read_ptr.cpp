//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/exception.hpp>
#include <sge/libpng/create_struct.hpp>
#include <sge/libpng/error_context_fwd.hpp>
#include <sge/libpng/png.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <fcppt/text.hpp>


sge::libpng::read_ptr::read_ptr(
	sge::libpng::error_context &_error_context
)
:
	ptr_(
		sge::libpng::create_struct(
			&::png_create_read_struct,
			_error_context
		)
	)
{
	if(
		ptr_
		==
		nullptr
	)
		throw
			sge::image::exception{
				FCPPT_TEXT("couldn't allocate png read structure")
			};
}

sge::libpng::read_ptr::~read_ptr()
{
	::png_destroy_read_struct(
		&ptr_,
		nullptr,
		nullptr
	);
}

png_structp
sge::libpng::read_ptr::ptr() const
{
	return
		ptr_;
}
