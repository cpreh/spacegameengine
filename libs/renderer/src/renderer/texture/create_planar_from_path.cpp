//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/file.hpp>
#include <sge/image2d/load_exn.hpp>
#include <sge/image2d/system_fwd.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_file.hpp>
#include <sge/renderer/texture/create_planar_from_path.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <filesystem>
#include <fcppt/config/external_end.hpp>



sge::renderer::texture::planar_unique_ptr
sge::renderer::texture::create_planar_from_path(
	std::filesystem::path const &_file,
	sge::renderer::device::core &_renderer,
	sge::image2d::system &_system,
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::resource_flags_field const &_flags,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
{
	return
		sge::renderer::texture::create_planar_from_file(
			_renderer,
			*sge::image2d::load_exn(
				_system,
				_file
			),
			_mipmap,
			_flags,
			_emulate_srgb
		);
}
