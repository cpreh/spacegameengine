/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef FCPPT_TEXTURE_PART_FRAGMENTED_HPP_INCLUDED
#define FCPPT_TEXTURE_PART_FRAGMENTED_HPP_INCLUDED

#include <sge/texture/part.hpp>
#include <sge/texture/fragmented_fwd.hpp>
#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <fcppt/math/box/basic_impl.hpp>

namespace sge
{
namespace texture
{

class part_fragmented
:
	public part
{
public:
	SGE_SYMBOL part_fragmented(
		renderer::lock_rect const &outer_rect,
		fragmented &,
		bool need_atlasing_w,
		bool need_atlasing_h
	);

	SGE_SYMBOL void
	data(
		image::view::const_object const &src
	);

	SGE_SYMBOL renderer::lock_rect const &
	area() const;

	SGE_SYMBOL renderer::texture_ptr const
	texture();

	SGE_SYMBOL renderer::const_texture_ptr const
	texture() const;

	SGE_SYMBOL bool
	repeatable() const;

	SGE_SYMBOL ~part_fragmented();
private:
	renderer::lock_rect outer_area_;
	fragmented &fragment;
	bool
		need_atlasing_w,
		need_atlasing_h;
	renderer::lock_rect inner_area_;
};


}
}

#endif
