//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/image2d/view/format.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/device/core.hpp>
#include <sge/renderer/device/core_ref.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/create_planar_from_view.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_unique_ptr.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/make_ref.hpp>


sge::renderer::texture::planar_unique_ptr
sge::renderer::texture::create_planar_from_view(
	sge::renderer::device::core_ref const _renderer,
	sge::image2d::view::const_object const &_view,
	sge::renderer::texture::mipmap::object const &_mipmap,
	sge::renderer::resource_flags_field const &_resource_flags,
	sge::renderer::texture::emulate_srgb const _emulate_srgb
)
{
	sge::renderer::texture::planar_unique_ptr tex(
		_renderer.get().create_planar_texture(
			sge::renderer::texture::planar_parameters(
				sge::image2d::view::size(
					_view
				),
				sge::renderer::texture::color_format(
					sge::image2d::view::format(
						_view
					),
					_emulate_srgb
				),
				_mipmap,
				_resource_flags,
				sge::renderer::texture::capabilities_field::null()
			)
		)
	);

	sge::renderer::texture::scoped_planar_lock const lock(
		fcppt::make_ref(
			*tex
		),
		sge::renderer::lock_mode::writeonly
	);

	sge::image2d::algorithm::copy_and_convert(
		_view,
		lock.value(),
		sge::image::algorithm::may_overlap::no,
		sge::image::algorithm::uninitialized::yes
	);

	return
		tex;
}
