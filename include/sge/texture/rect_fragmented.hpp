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


#ifndef SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_RECT_FRAGMENTED_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/texture/const_planar_ptr.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_fwd.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class SGE_CLASS_SYMBOL rect_fragmented
:
	public texture::fragmented
{
	FCPPT_NONCOPYABLE(
		rect_fragmented
	);
public:
	SGE_TEXTURE_SYMBOL rect_fragmented(
		renderer::device &,
		image::color::format::type,
		renderer::texture::mipmap::object const &,
		renderer::dim2 const &initial_size
	);

	SGE_TEXTURE_SYMBOL
	~rect_fragmented();
private:
	texture::part_ptr const
	consume_fragment(
		renderer::dim2 const &
	);

	void
	on_return_fragment(
		texture::part const &
	);

	renderer::texture::planar_ptr const
	texture();

	renderer::texture::const_planar_ptr const
	texture() const;

	bool
	repeatable() const;

	texture::free_type
	free_value() const;

	bool
	empty() const;

	renderer::size_type
		cur_x_,
		cur_y_,
		cur_height_;

	renderer::texture::planar_ptr const tex_;

	renderer::size_type texture_count_;
};

}
}

#endif
