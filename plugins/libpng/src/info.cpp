//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/exception.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/png.hpp>
#include <fcppt/text.hpp>


sge::libpng::info::info(
	png_structp const _ptr
)
:
	ptr_(
		_ptr
	),
	info_(
		::png_create_info_struct(
			_ptr
		)
	)
{
	if(
		!info_
	)
		throw
			sge::image::exception{
				FCPPT_TEXT("couldn't generate png info structure")
			};
}

sge::libpng::info::~info()
{
	::png_destroy_info_struct(
		ptr_,
		&info_
	);
}

png_infop
sge::libpng::info::get() const
{
	return
		info_;
}
