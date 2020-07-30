//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/libpng/gamma.hpp>
#include <sge/libpng/get_gamma.hpp>
#include <sge/libpng/info.hpp>
#include <sge/libpng/read_ptr.hpp>
#include <sge/libpng/srgb_gamma.hpp>


sge::libpng::gamma
sge::libpng::get_gamma(
	sge::libpng::read_ptr const &_read_ptr,
	sge::libpng::info const &_info
)
{
	sge::libpng::gamma::value_type gamma_raw{};

	return
		::png_get_gAMA(
			_read_ptr.ptr(),
			_info.get(),
			&gamma_raw
		)
		==
		0
		?
			sge::libpng::srgb_gamma()
		:
			sge::libpng::gamma(
				gamma_raw
			)
		;
}
