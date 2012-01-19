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


#ifndef SGE_D3D9_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_HPP_INCLUDED

#include <sge/d3d9/d3dinclude.hpp>
#include <sge/d3d9/resource.hpp>
#include <sge/d3d9/usage.hpp>
#include <sge/d3d9/texture/base.hpp>
#include <sge/d3d9/texture/basic_fwd.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/com_deleter.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


namespace sge
{
namespace d3d9
{
namespace texture
{

template<
	typename Types
>
class basic
:
	public Types::base,
	public d3d9::texture::base,
	public d3d9::resource
{
	FCPPT_NONCOPYABLE(
		basic
	);
public:
	typedef typename Types::base base;

	typedef typename base::image_tag image_tag;

	typedef typename Types::parameters parameters_type;

	typedef typename Types::d3d_type d3d_type;

	basic(
		IDirect3DDevice9 *,
		parameters_type const &
	);

	~basic();

	sge::renderer::resource_flags_field const
	resource_flags() const;

	sge::renderer::texture::capabilities_field const
	capabilities() const;

	sge::renderer::texture::mipmap::object const
	mipmap() const;

	d3d_type *
	get() const;
protected:
	parameters_type const &
	parameters() const;

	typedef typename base::view view;

	typedef typename base::const_view const_view;

	typedef typename base::lock_area lock_area;

	typedef typename Types::lock_function lock_function;

	typedef typename Types::unlock_function unlock_function;

	view const
	lock_impl(
		lock_function const &,
		lock_area const &,
		renderer::lock_mode::type
	);

	const_view const
	lock_impl(
		lock_function const &,
		lock_area const &
	) const;

	void
	unlock_impl(
		unlock_function const &
	) const;
private:
	template<
		typename View,
		typename MakeView
	>
	View const
	do_lock(
		MakeView const &,
		lock_function const &,
		lock_area const &,
		renderer::lock_flags::method::type
	) const;

	typedef typename Types::unique_ptr d3d_unique_ptr;

	d3d_unique_ptr
	create(
		D3DPOOL,
		d3d9::usage
	) const;

	void
	init();

	void
	on_reset();

	void
	on_loss();

	typedef typename Types::locked_dest locked_dest;

	IDirect3DDevice9 *const device_;

	parameters_type const parameters_;

	D3DFORMAT const d3d_color_format_;

	sge::image::color::format::type const color_format_;

	d3d9::usage const usage_;

	typedef fcppt::scoped_ptr<
		d3d_type,
		fcppt::com_deleter
	> d3d_scoped_ptr;

	d3d_scoped_ptr main_texture_;

	mutable d3d_scoped_ptr temp_texture_;

	mutable locked_dest locked_dest_;
};

}
}
}

#endif
