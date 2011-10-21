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


#ifndef SGE_TEXTURE_NO_FRAGMENTED_HPP_INCLUDED
#define SGE_TEXTURE_NO_FRAGMENTED_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/texture/address_mode2.hpp>
#include <sge/renderer/texture/const_planar_ptr.hpp>
#include <sge/renderer/texture/planar_ptr.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <sge/texture/fragmented.hpp>
#include <sge/texture/part_ptr.hpp>
#include <sge/texture/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace texture
{

class SGE_CLASS_SYMBOL no_fragmented
:
	public texture::fragmented
{
	FCPPT_NONCOPYABLE(
		no_fragmented
	);
public:
	SGE_TEXTURE_SYMBOL
	no_fragmented(
		renderer::device &,
		image::color::format::type,
		renderer::texture::mipmap::object const &,
		renderer::texture::address_mode2 const &
	);

	SGE_TEXTURE_SYMBOL
	~no_fragmented();
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

	free_type
	free_value() const;

	bool
	empty() const;

	renderer::device &rend_;

	image::color::format::type const format_;

	renderer::texture::mipmap::object const mipmap_;

	renderer::texture::address_mode2 const address_mode_;

	renderer::texture::planar_ptr tex_;
};

}
}

#endif

