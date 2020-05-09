//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load_raw_exn.hpp>
#include <sge/audio/loader.hpp>
#include <sge/audio/loader_ref.hpp>
#include <sge/media/const_raw_range.hpp>
#include <sge/media/optional_extension_fwd.hpp>
#include <sge/media/impl/load_raw_exn.hpp>


sge::audio::file_unique_ptr
sge::audio::load_raw_exn(
	sge::audio::loader_ref const _loader,
	sge::media::const_raw_range const &_range,
	sge::media::optional_extension const &_extension
)
{
	return
		sge::media::impl::load_raw_exn<
			sge::audio::file_unique_ptr,
			sge::audio::exception
		>(
			_loader,
			_range,
			_extension
		);
}
