//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/algorithm/uninitialized.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/sub_data.hpp>
#include <sge/texture/atlasing/border_h.hpp>
#include <sge/texture/atlasing/border_w.hpp>
#include <sge/texture/atlasing/make_inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect.hpp>


sge::texture::part_fragmented::part_fragmented(
	sge::texture::fragmented &_fragment,
	sge::texture::atlasing::outer_rect const &_outer_area
)
:
	fragment_(
		_fragment
	),
	inner_area_(
		sge::texture::atlasing::make_inner_rect(
			_outer_area
		)
	)
{
}

sge::texture::part_fragmented::~part_fragmented()
{
	fragment_.return_fragment(
		*this
	);
}

void
sge::texture::part_fragmented::data(
	sge::image2d::view::const_object const &_src,
	sge::image::algorithm::uninitialized const _uninitialized
)
{
	sge::texture::sub_data(
		this->texture(),
		_src,
		inner_area_.get().pos(),
		_uninitialized
	);

	sge::texture::atlasing::border_h(
		this->texture(),
		_src,
		inner_area_,
		_uninitialized
	);

	sge::texture::atlasing::border_w(
		this->texture(),
		_src,
		inner_area_,
		_uninitialized
	);
}

sge::renderer::lock_rect
sge::texture::part_fragmented::area() const
{
	return
		inner_area_.get();
}

sge::renderer::texture::planar &
sge::texture::part_fragmented::texture() const
{
	return
		fragment_.texture();
}

bool
sge::texture::part_fragmented::repeatable() const
{
	return
		false;
}
