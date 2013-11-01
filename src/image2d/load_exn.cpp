#include <sge/image/exception.hpp>
#include <sge/image2d/file.hpp>
#include <sge/image2d/file_unique_ptr.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system.hpp>
#include <sge/src/media/load_exn.hpp>
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
		sge::media::load_exn<
			sge::image2d::file_unique_ptr,
			sge::image::exception
		>(
			_system,
			_path
		);
}
