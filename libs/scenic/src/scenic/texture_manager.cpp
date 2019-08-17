//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/mipmap/all_levels.hpp>
#include <sge/scenic/texture_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sge::scenic::texture_manager::texture_manager(
	sge::renderer::device::core &_renderer,
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
	std::filesystem::path const &_path)
{
	path_to_texture_map::iterator it =
		path_to_texture_.find(
			_path);

	if(it != path_to_texture_.end())
		return *(it->second);

	return
		*path_to_texture_.insert(
			std::make_pair(
				_path,
				sge::renderer::texture::create_planar_from_path(
					_path,
					renderer_,
					image_loader_,
					sge::renderer::texture::mipmap::all_levels(
						sge::renderer::texture::mipmap::auto_generate::yes),
					sge::renderer::resource_flags_field::null(),
					sge::renderer::texture::emulate_srgb::no))).first->second;
}

sge::scenic::texture_manager::~texture_manager()
{
}
