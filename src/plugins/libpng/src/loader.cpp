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
	image::view::const_object const&p)
{
	return
		image::file_ptr(
			new file(
				p));
}

sge::extension_set const
sge::libpng::loader::extensions() const
{
	extension_set s;
	s.insert(FCPPT_TEXT("png"));
	return s;
}
