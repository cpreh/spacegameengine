#include "../loader.hpp"
#include "../file.hpp"
#include <sge/image/file_fwd.hpp>
#include <fcppt/make_shared_ptr.hpp>

sge::image::file_ptr const sge::libpng::loader::load(
	fcppt::filesystem::path const &_path
)
{
	return
		fcppt::make_shared_ptr<
			file
		>(
			_path
		);
}

sge::image::file_ptr const sge::libpng::loader::create(
	image::view::const_object const&p)
{
	return
		fcppt::make_shared_ptr<
			file
		>(
			p
		);
}

sge::extension_set const
sge::libpng::loader::extensions() const
{
	extension_set s;
	s.insert(FCPPT_TEXT("png"));
	return s;
}
