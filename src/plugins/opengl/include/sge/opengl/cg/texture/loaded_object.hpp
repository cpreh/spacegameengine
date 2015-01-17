/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_OPENGL_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CG_TEXTURE_LOADED_OBJECT_HPP_INCLUDED

#include <sge/cg/parameter/object.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/base_fwd.hpp>
#include <sge/opengl/texture/bind_context_fwd.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture.hpp>
#include <sge/renderer/texture/base_fwd.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace cg
{
namespace texture
{

class loaded_object
:
	public sge::renderer::cg::loaded_texture
{
	FCPPT_NONCOPYABLE(
		loaded_object
	);
public:
	loaded_object(
		sge::opengl::context::system::object &,
		sge::opengl::context::device::object &,
		sge::cg::parameter::object const &,
		sge::renderer::texture::base &
	);

	~loaded_object()
	override;

	sge::renderer::texture::stage const
	enable() const;

	void
	disable() const;
private:
	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object &device_context_;

	sge::opengl::texture::bind_context &bind_context_;

	sge::cg::parameter::object const parameter_;

	sge::opengl::texture::base const &texture_;

	sge::renderer::texture::stage const stage_;
};

}
}
}
}

#endif
