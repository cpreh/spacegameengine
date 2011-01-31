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


#ifndef SGE_RENDERER_TEXTURE_RW_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_RW_HPP_INCLUDED

#include <sge/renderer/texture_ptr.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/symbol.hpp>
#include <sge/class_symbol.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class SGE_CLASS_SYMBOL texture_rw
:
	public texture
{
	FCPPT_NONCOPYABLE(texture_rw)
public:
	SGE_SYMBOL texture_rw(
		texture_ptr read,
		texture_ptr write
	);

	SGE_SYMBOL ~texture_rw();

	SGE_SYMBOL dim_type const
	dim() const;

	SGE_SYMBOL image2d::view::object const
	lock(
		lock_rect const &,
		lock_mode::type
	);

	SGE_SYMBOL image2d::view::const_object const
	lock(
		lock_rect const &
	) const;

	SGE_SYMBOL void
	unlock() const;

	SGE_SYMBOL
	renderer::color_surface_ptr const
	surface(
		renderer::stage_type
	);

	SGE_SYMBOL
	sge::renderer::stage_type
	stages() const;

	SGE_SYMBOL resource_flags_field const
	flags() const;

	SGE_SYMBOL texture_ptr const
	read() const;

	SGE_SYMBOL texture_ptr const
	write() const;

	class lock_data;
private:
	mutable texture_ptr
		read_,
		write_;

	mutable fcppt::scoped_ptr<
		lock_data
	> locked_;
};

}
}

#endif
