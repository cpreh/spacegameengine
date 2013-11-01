#include <sge/audio/exception.hpp>
#include <sge/audio/file.hpp>
#include <sge/audio/file_unique_ptr.hpp>
#include <sge/audio/load_exn.hpp>
#include <sge/audio/loader.hpp>
#include <sge/src/media/load_exn.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/filesystem/path.hpp>
#include <fcppt/config/external_end.hpp>


sge::audio::file_unique_ptr
sge::audio::load_exn(
	sge::audio::loader &_loader,
	boost::filesystem::path const &_path
)
{
	return
		sge::media::load_exn<
			sge::audio::file_unique_ptr,
			sge::audio::exception
		>(
			_loader,
			_path
		);
}
