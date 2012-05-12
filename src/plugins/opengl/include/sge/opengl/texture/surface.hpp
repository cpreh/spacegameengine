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


#ifndef SGE_OPENGL_TEXTURE_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SURFACE_HPP_INCLUDED

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_surface.hpp>
#include <sge/opengl/texture/binding_fwd.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/lock_base_fwd.hpp>
#include <sge/opengl/texture/surface_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/mipmap/level.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class surface
:
	public sge::opengl::texture::basic_surface<
		sge::renderer::color_surface
	>
{
	FCPPT_NONCOPYABLE(
		surface
	);
public:
	typedef opengl::texture::basic_surface<
		sge::renderer::color_surface
	> base;

	surface(
		sge::opengl::texture::binding const &,
		sge::opengl::context::system::object &,
		sge::opengl::texture::type,
		sge::opengl::texture::id,
		sge::renderer::texture::mipmap::level,
		sge::renderer::resource_flags_field const &,
		sge::opengl::color_format,
		sge::opengl::color_format_type,
		bool is_render_target
	);

	~surface();

	bool
	is_render_target() const;
private:
	base::const_view const
	lock(
		rect const &
	) const;

	void
	unlock() const;

	sge::opengl::context::system::object &system_context_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::opengl::color_format const color_format_;

	sge::opengl::color_format_type const color_format_type_;

	bool const is_render_target_;

	typedef fcppt::scoped_ptr<
		sge::opengl::texture::lock_base
	> lock_scoped_ptr;

	mutable lock_scoped_ptr lock_;
};

}
}
}

#endif
