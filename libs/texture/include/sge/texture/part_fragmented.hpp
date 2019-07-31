//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_PART_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_PART_FRAGMENTED_HPP_INCLUDED

#include <sge/image/algorithm/uninitialized_fwd.hpp>
#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect_fwd.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class part_fragmented
:
	public sge::texture::part
{
	FCPPT_NONCOPYABLE(
		part_fragmented
	);
public:
	SGE_TEXTURE_DETAIL_SYMBOL
	part_fragmented(
		sge::texture::fragmented &,
		sge::texture::atlasing::outer_rect const &
	);

	SGE_TEXTURE_DETAIL_SYMBOL
	void
	data(
		sge::image2d::view::const_object const &,
		sge::image::algorithm::uninitialized
	)
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::lock_rect
	area() const
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::texture::planar &
	texture() const
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	bool
	repeatable() const
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	~part_fragmented()
	override;
private:
	sge::texture::fragmented &fragment_;

	sge::texture::atlasing::inner_rect const inner_area_;
};

}
}

#endif
