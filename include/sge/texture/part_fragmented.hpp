/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/texture/part.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/renderer/texture/const_planar_ptr.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace texture
{

class part_fragmented
:
	public texture::part
{
	FCPPT_NONCOPYABLE(
		part_fragmented
	);
public:
	SGE_TEXTURE_SYMBOL
	part_fragmented(
		renderer::lock_rect const &outer_rect,
		fragmented &,
		bool need_atlasing_w,
		bool need_atlasing_h
	);

	SGE_TEXTURE_SYMBOL
	void
	data(
		image2d::view::const_object const &
	);

	SGE_TEXTURE_SYMBOL
	renderer::lock_rect const &
	area() const;

	SGE_TEXTURE_SYMBOL
	renderer::texture::planar_ptr const
	texture();

	SGE_TEXTURE_SYMBOL
	renderer::texture::const_planar_ptr const
	texture() const;

	SGE_TEXTURE_SYMBOL
	bool
	repeatable() const;

	SGE_TEXTURE_SYMBOL
	~part_fragmented();
private:
	renderer::lock_rect outer_area_;

	texture::fragmented &fragment_;

	bool
		need_atlasing_w_,
		need_atlasing_h_;

	renderer::lock_rect inner_area_;
};

}
}

#endif
