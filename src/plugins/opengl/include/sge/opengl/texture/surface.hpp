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


#ifndef SGE_OPENGL_TEXTURE_SURFACE_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_SURFACE_HPP_INCLUDED

#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/texture/basic_surface.hpp>
#include <sge/opengl/texture/id.hpp>
#include <sge/opengl/texture/lock_base_fwd.hpp>
#include <sge/opengl/texture/scoped_work_bind_fwd.hpp>
#include <sge/opengl/texture/surface_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/color_surface.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
#include <fcppt/container/bitfield/basic_impl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class surface
:
	public opengl::texture::basic_surface<
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
		texture::scoped_work_bind const &,
		opengl::context::object &,
		texture::type,
		texture::id,
		renderer::texture::stage,
		renderer::resource_flags_field const &,
		opengl::color_format,
		opengl::color_format_type,
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

	opengl::context::object &context_;

	sge::renderer::texture::stage const stage_;

	renderer::resource_flags_field const resource_flags_;

	opengl::color_format const color_format_;

	opengl::color_format_type const color_format_type_;

	bool const is_render_target_;

	typedef fcppt::scoped_ptr<
		texture::lock_base
	> lock_scoped_ptr;

	mutable lock_scoped_ptr lock_;
};

}
}
}

#endif
