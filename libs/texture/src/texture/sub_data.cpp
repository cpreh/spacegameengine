//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/view/size.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/texture/pos.hpp>
#include <sge/texture/sub_data.hpp>


void
sge::texture::sub_data(
	sge::renderer::texture::planar &_texture,
	sge::image2d::view::const_object const &_view,
	sge::texture::pos const _pos,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::renderer::texture::scoped_planar_lock const lock(
		_texture,
		sge::renderer::lock_rect(
			_pos,
			sge::image2d::view::size(
				_view
			)
		),
		sge::renderer::lock_mode::writeonly
	);

	sge::image2d::algorithm::copy_and_convert(
		_view,
		lock.value(),
		sge::image::algorithm::may_overlap::no,
		_uninitialized
	);
}
