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


#ifndef SGE_OPENGL_TEXTURE_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_OBJECT_HPP_INCLUDED

#include "object_fwd.hpp"
#include "basic.hpp"
#include "optional_type.hpp"
#include "scoped_work_bind_fwd.hpp"
#include "../context/object_fwd.hpp"
#include <sge/image/color/format.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{
namespace texture
{

namespace detail
{

typedef texture::basic<
	renderer::texture
> object_base;

}

class object
:
	public detail::object_base
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef detail::object_base object_base;

	object(
		context::object &,
		object_base::dim_type const &,
		image::color::format::type,
		renderer::filter::texture const &,
		renderer::resource_flags_field const &,
		opengl::texture::optional_type const &
	);

	~object();
private:
	typedef object_base::pointer pointer;

	void
	set_area(
		opengl::texture::scoped_work_bind const &,
		lock_area const &,
		pointer
	) const;

	renderer::color_surface_ptr const
	surface(
		renderer::stage_type
	);

	sge::renderer::stage_type
	stages() const;
};

}
}
}

#endif
