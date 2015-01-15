/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#ifndef SGE_TEXTURE_PART_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_PART_FRAGMENTED_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect_fwd.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/detail/symbol.hpp>
#include <sge/texture/atlasing/inner_rect.hpp>
#include <sge/texture/atlasing/outer_rect_fwd.hpp>
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
		sge::image2d::view::const_object const &
	)
	override;

	SGE_TEXTURE_DETAIL_SYMBOL
	sge::renderer::lock_rect const
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
