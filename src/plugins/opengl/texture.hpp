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


#ifndef SGE_OPENGL_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_HPP_INCLUDED

#include "texture_fwd.hpp"
#include "common.hpp"
#include "basic_texture.hpp"
#include "context/object_fwd.hpp"
#include <sge/image/color/format.hpp>
#include <sge/renderer/color_surface_ptr.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/renderer/texture.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/filter/texture_fwd.hpp>
#include <fcppt/optional_fwd.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace opengl
{

namespace detail
{

typedef basic_texture<
	renderer::texture
> texture_base;

}

class texture
:
	public detail::texture_base
{
	FCPPT_NONCOPYABLE(
		texture
	);
public:
	typedef detail::texture_base base;

	typedef fcppt::optional<
		GLenum
	> optional_type;

	texture(
		context::object &,
		base::dim_type const &,
		image::color::format::type,
		renderer::filter::texture const &,
		renderer::resource_flags_field const &,
		optional_type const &
	);

	~texture();
private:
	typedef base::pointer pointer;

	void
	set_area(
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

#endif

