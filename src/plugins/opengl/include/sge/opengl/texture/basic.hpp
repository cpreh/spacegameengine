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


#ifndef SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_HPP_INCLUDED

#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/base.hpp>
#include <sge/opengl/texture/basic_fwd.hpp>
#include <sge/opengl/texture/basic_parameters_fwd.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic
:
	public Types::base,
	public sge::opengl::texture::base
{
	FCPPT_NONCOPYABLE(
		basic
	);
protected:
	typedef typename Types::parameters parameters_type;

	basic(
		sge::opengl::texture::basic_parameters const &,
		sge::opengl::texture::type,
		parameters_type const &
	);

	~basic();

	typedef typename Types::base base_type;

	sge::renderer::resource_flags_field const
	resource_flags() const;

	sge::renderer::texture::capabilities_field const
	capabilities() const;

	sge::renderer::texture::mipmap::object const
	mipmap() const;

	sge::opengl::context::system::object &
	system_context() const;

	sge::opengl::context::device::object &
	device_context() const;
private:
	void
	generate_mipmaps();

	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object &device_context_;

	sge::renderer::resource_flags_field const resource_flags_;

	sge::renderer::texture::capabilities_field const capabilities_;

	sge::renderer::texture::mipmap::object const mipmap_;
};

}
}
}

#endif
