//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_raw_exn.hpp>
#include <sge/image2d/system.hpp>
#include <sge/image2d/system_ref.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/impl/load_raw_exn.hpp>


sge::image2d::file_unique_ptr
sge::image2d::load_raw_exn(
	sge::image2d::system_ref const _system,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		sge::media::impl::load_raw_exn<
			sge::image2d::file_unique_ptr,
			sge::image2d::exception
		>(
			_system,
			_range,
			_extension
		);
}
