/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_TEXTURE_BASIC_PART_RAW_HPP_INCLUDED
#define SGE_TEXTURE_BASIC_PART_RAW_HPP_INCLUDED

#include <sge/image2d/view/const_object_fwd.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/texture/planar_fwd.hpp>
#include <sge/texture/basic_part_raw_fwd.hpp>
#include <sge/texture/part.hpp>
#include <sge/texture/symbol.hpp>
#include <sge/texture/detail/ref_store_type.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace texture
{

template<
	typename Ref
>
class basic_part_raw
:
	public sge::texture::part
{
public:
	typedef Ref ref_type;

	SGE_TEXTURE_SYMBOL
	explicit
	basic_part_raw(
		Ref
	);

	SGE_TEXTURE_SYMBOL
	basic_part_raw(
		Ref,
		sge::renderer::lock_rect const &
	);

	SGE_TEXTURE_SYMBOL
	~basic_part_raw();

	SGE_TEXTURE_SYMBOL
	void
	data(
		sge::image2d::view::const_object const &
	);

	SGE_TEXTURE_SYMBOL
	sge::renderer::lock_rect const
	area() const;

	SGE_TEXTURE_SYMBOL
	sge::renderer::texture::planar &
	texture();

	SGE_TEXTURE_SYMBOL
	sge::renderer::texture::planar const &
	texture() const;

	SGE_TEXTURE_SYMBOL
	bool
	repeatable() const;
private:
	typedef typename sge::texture::detail::ref_store_type<
		Ref
	>::type store_type;

	store_type texture_;

	sge::renderer::lock_rect const area_;
};

}
}

#endif
