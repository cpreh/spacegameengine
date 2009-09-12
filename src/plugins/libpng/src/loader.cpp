#include "../loader.hpp"
#include "../file.hpp"
#include <sge/image/file_fwd.hpp>

sge::image::file_ptr const sge::libpng::loader::load(
	filesystem::path const &_path)
{
	return 
		image::file_ptr(
			new file(
				_path));
}

sge::image::file_ptr const sge::libpng::loader::create(
	image::view::const_object const&)
{
	return 
		image::file_ptr();
}
