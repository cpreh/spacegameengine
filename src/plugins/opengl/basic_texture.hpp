/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_OPENGL_BASIC_TEXTURE_HPP_INCLUDED
#define SGE_OPENGL_BASIC_TEXTURE_HPP_INCLUDED

#include "common.hpp"
#include "texture_lock.hpp"
#include "texture_base.hpp"
#include "lock_method.hpp"
#include "context/object_fwd.hpp"
#include <sge/renderer/filter/texture.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/traits/pitch.hpp>
#include <fcppt/container/bitfield/basic_decl.hpp>
#include <fcppt/math/box/basic_decl.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sge
{
namespace opengl
{

template<
	typename Base
>
class basic_texture
:
	public Base,
	public texture_base
{
public:
	typedef texture_lock::pointer pointer;
	typedef texture_lock::const_pointer const_pointer;

	typedef typename Base::size_type size_type;
	typedef typename Base::dim_type dim_type;
	typedef typename Base::lock_area lock_area;
	typedef typename Base::view_type view_type;
	typedef typename Base::const_view_type const_view_type;

	// implementation for base class
	dim_type const
	dim() const;

	view_type const
	lock(
		lock_area const &,
		renderer::lock_mode::type
	);

	const_view_type const
	lock(
		lock_area const &
	) const;

	void
	unlock() const;
private:
	// helper functions
	void
	lock_me(
		lock_area const &,
		lock_method::type
	) const;

	view_type const
	view();

	const_view_type const
	view() const;

	dim_type const
	lock_dim() const;
protected:
	renderer::filter::texture const &
	filter() const;

	using Base::content;

	size_type
	stride() const;

	GLenum
	format() const;

	GLenum
	format_type() const;

	GLenum
	internal_format() const;

	basic_texture(
		opengl::context::object &,
		renderer::filter::texture const &,
		renderer::resource_flags_field const &,
		GLenum type,
		image::color::format::type,
		dim_type const &
	);

	opengl::context::object &
	context() const;
public:
	~basic_texture();

	renderer::resource_flags_field const
	flags() const;
private:
	virtual void
	set_area(
		lock_area const &,
		pointer dest
	) const = 0;

	void
	check_locked() const;

	void
	check_not_locked() const;

	opengl::context::object &context_;

	renderer::filter::texture const filter_;

	renderer::resource_flags_field const flags_;

	dim_type const dim_;

	GLenum const
		format_,
		format_type_,
		internal_format_;

	size_type const stride_;

	typedef fcppt::scoped_ptr<
		texture_lock
	> scoped_lock_ptr;

	mutable scoped_lock_ptr lock_;

	typedef fcppt::optional<
		lock_area
	> optional_lock_area;

	mutable optional_lock_area lock_area_;

	typedef fcppt::optional<
		typename sge::image::traits::pitch<
			typename Base::image_tag
		>::type
	> optional_pitch;
};

}
}

#endif

