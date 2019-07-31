//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/lock_rect.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <sge/texture/atlasing/make_inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>
#include <fcppt/math/box/shrink.hpp>
#include <fcppt/math/vector/fill.hpp>


sge::texture::atlasing::inner_rect
sge::texture::atlasing::make_inner_rect(
	sge::texture::atlasing::outer_rect const &_outer
)
{
	return
		sge::texture::atlasing::inner_rect(
			fcppt::math::box::shrink(
				_outer.get(),
				fcppt::math::vector::fill<
					sge::renderer::lock_rect::vector
				>(
					1u
				)
			)
		);
}
