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


#ifndef SGE_RENDERER_TEXTURE_SOFTWARE_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_SOFTWARE_HPP_INCLUDED

#include <sge/renderer/texture.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/view/object.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/container/raw_vector_decl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL texture_software
:
	public texture
{
	FCPPT_NONCOPYABLE(texture_software)
public:
	SGE_SYMBOL texture_software(
		dim_type const &,
		image::color::format::type
	);

	SGE_SYMBOL ~texture_software();

	SGE_SYMBOL dim_type const
	dim() const;

	SGE_SYMBOL image::view::object const
	lock(
		lock_rect const &,
		lock_mode::type
	);

	SGE_SYMBOL image::view::const_object const
	lock(
		lock_rect const &
	) const;

	SGE_SYMBOL void
	unlock() const;

	SGE_SYMBOL resource_flags_field const
	flags() const;
private:
	typedef fcppt::container::raw_vector<
		unsigned char
	> internal_vector;

	dim_type dim_;

	image::color::format::type const cf;

	internal_vector raw_bytes;
	// has to be mutable for unlock
	mutable bool locked;

	internal_vector::size_type
	byte_count() const;

	void
	resize(
		dim_type const &
	);
};

}
}

#endif
