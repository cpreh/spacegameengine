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


#ifndef SGE_OPENGL_TEXTURE_BASIC_BUFFER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_BASIC_BUFFER_HPP_INCLUDED

#include <sge/image/traits/color_tag.hpp>
#include <sge/image/traits/format.hpp>
#include <sge/image/traits/pitch_fwd.hpp>
#include <sge/opengl/color_format.hpp>
#include <sge/opengl/color_format_type.hpp>
#include <sge/opengl/internal_color_format.hpp>
#include <sge/opengl/context/device/object_fwd.hpp>
#include <sge/opengl/context/system/object_fwd.hpp>
#include <sge/opengl/texture/basic_buffer_parameters_fwd.hpp>
#include <sge/opengl/texture/basic_fwd.hpp>
#include <sge/opengl/texture/buffer_base.hpp>
#include <sge/opengl/texture/is_render_target.hpp>
#include <sge/opengl/texture/lock_base.hpp>
#include <sge/opengl/texture/type.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/math/box/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

template<
	typename Types
>
class basic_buffer
:
	public Types::base,
	public sge::opengl::texture::buffer_base
{
	FCPPT_NONCOPYABLE(
		basic_buffer
	);
public:
	typedef typename Types::base base_type;

	typedef typename base_type::image_tag image_tag;

	typedef typename sge::image::traits::color_tag<
		image_tag
	>::type color_tag;

	typedef typename sge::image::traits::format<
		color_tag
	>::type format_type;

	basic_buffer(
		format_type,
		sge::opengl::texture::basic_buffer_parameters const &
	);

	~basic_buffer();

	typedef sge::opengl::texture::lock_base::pointer pointer;

	typedef sge::opengl::texture::lock_base::const_pointer const_pointer;

	typedef typename base_type::size_type size_type;

	typedef typename base_type::dim dim;

	typedef typename base_type::lock_area lock_area;

	typedef typename base_type::view view;

	typedef typename base_type::const_view const_view;

	sge::opengl::texture::is_render_target const
	is_render_target() const;
private:
	// implementation for base class
	dim const
	size() const;

	format_type
	format() const;

	view const
	lock(
		lock_area const &,
		sge::renderer::lock_mode::type
	);

	const_view const
	lock(
		lock_area const &
	) const;

	void
	unlock() const;

	// helper functions
	void
	lock_me(
		lock_area const &,
		sge::renderer::lock_flags::method::type
	) const;

	view const
	lock_view();

	const_view const
	lock_view() const;

	dim const
	lock_dim() const;

	void
	check_locked() const;

	void
	check_not_locked() const;

	sge::opengl::context::system::object &system_context_;

	sge::opengl::context::device::object &device_context_;

	sge::opengl::texture::type const type_;

	sge::renderer::resource_flags_field const resource_flags_;

	dim const size_;

	format_type const format_;

	sge::opengl::color_format const color_format_;

	sge::opengl::color_format_type const color_format_type_;

	sge::opengl::internal_color_format const internal_color_format_;

	sge::opengl::texture::is_render_target const is_render_target_;

	size_type const stride_;

	typedef fcppt::scoped_ptr<
		sge::opengl::texture::lock_base
	> scoped_lock_ptr;

	mutable scoped_lock_ptr lock_;

	typedef fcppt::optional<
		lock_area
	> optional_lock_area;

	mutable optional_lock_area lock_area_;

	typedef typename sge::image::traits::pitch<
		image_tag
	>::type pitch;
};

}
}
}

#endif
