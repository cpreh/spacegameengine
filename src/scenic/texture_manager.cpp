#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <fcppt/container/bitfield/object_impl.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>


sge::scenic::texture_manager::texture_manager(
	sge::renderer::device &_renderer,
	sge::image2d::system &_image_loader)
:
	renderer_(
		_renderer),
	image_loader_(
		_image_loader),
	path_to_texture_()
{
}

sge::renderer::texture::planar &
sge::scenic::texture_manager::texture_for_path(
	boost::filesystem::path const &_path)
{
	path_to_texture_map::iterator it =
		path_to_texture_.find(
			_path);

	if(it != path_to_texture_.end())
		return *(it->second);

	return
		fcppt::container::ptr::insert_unique_ptr_map(
			path_to_texture_,
			_path,
			sge::renderer::texture::create_planar_from_path(
				_path,
				renderer_,
				image_loader_,
				sge::renderer::texture::mipmap::all_levels(
					sge::renderer::mipmap::auto_generate::yes),
				sge::renderer::resource_flags::null())).first->second;
}

sge::scenic::texture_manager::~texture_manager()
{
}
