//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/image2d/view/sub.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/pos.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_h.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <fcppt/math/vector/null.hpp>


void
sge::texture::atlasing::border_h(
	sge::renderer::texture::planar &_texture,
	sge::image2d::view::const_object const &_source,
	sge::texture::atlasing::inner_rect const &_inner_area,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::renderer::dim2 const dim(
		sge::image2d::view::size(
			_source
		)
	);

	sge::texture::sub_data(
		_texture,
		sge::image2d::view::sub(
			_source,
			sge::renderer::lock_rect(
				fcppt::math::vector::null<
					sge::renderer::lock_rect::vector
				>(),
				sge::renderer::lock_rect::dim(
					dim.w(),
					1U
				)
			)
		),
		sge::texture::pos(
			_inner_area.get().left(),
			_inner_area.get().top() - 1U
		),
		_uninitialized
	);

	sge::texture::sub_data(
		_texture,
		sge::image2d::view::sub(
			_source,
			sge::renderer::lock_rect(
				sge::renderer::lock_rect::vector(
					0U,
					dim.h() - 1U
				),
				sge::renderer::lock_rect::dim(
					dim.w(),
					1U
				)
			)
		),
		sge::texture::pos(
			_inner_area.get().left(),
			_inner_area.get().bottom() + 1U
		),
		_uninitialized
	);
}
