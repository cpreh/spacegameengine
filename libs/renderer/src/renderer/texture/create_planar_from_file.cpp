//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image2d/file.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/texture/create_planar_from_file.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>


sge::renderer::texture::planar_unique_ptr
sge::renderer::texture::create_planar_from_file(
	sge::renderer::device::core &_renderer,
	sge::image2d::file &_file,
	sge::renderer::texture::mipmap::object const &_filter,
	sge::renderer::resource_flags_field const &_flags,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
{
	return
		sge::renderer::texture::create_planar_from_view(
			_renderer,
			_file.view(),
			_filter,
			_flags,
			_emulate_srgb
		);
}
