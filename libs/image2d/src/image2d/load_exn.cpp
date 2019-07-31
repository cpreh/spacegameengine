//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_exception.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system.hpp>
#include <sge/media/impl/load_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::image2d::file_unique_ptr
sge::image2d::load_exn(
	sge::image2d::system &_system,
	boost::filesystem::path const &_path
)
{
	return
		sge::media::impl::load_exn<
			sge::image2d::file_unique_ptr,
			sge::image2d::exception
		>(
			_system,
			_path
		);
}
