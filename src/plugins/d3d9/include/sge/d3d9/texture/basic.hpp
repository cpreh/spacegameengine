/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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
#include <sge/d3d9/texture/basic_buffer_fwd.hpp>
#include <sge/d3d9/texture/basic_fwd.hpp>
#include <sge/image/color/format.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field_fwd.hpp>
#include <sge/renderer/lock_flags/method.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/mipmap/level_count.hpp>
#include <sge/renderer/texture/mipmap/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>


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
	public sge::d3d9::texture::base,
	public sge::d3d9::resource
{
	FCPPT_NONCOPYABLE(
		basic
	);
public:
	typedef typename Types::base base;

	typedef typename Types::parameters parameters_type;

	typedef typename Types::d3d_type d3d_type;

	typedef sge::d3d9::texture::basic_buffer<
		Types
	> buffer_type;

	basic(
		IDirect3DDevice9 &,
		parameters_type const &
	);

	~basic();
protected:
	sge::renderer::resource_flags_field const
	resource_flags() const;
private:
	sge::renderer::texture::capabilities_field const
	capabilities() const;

	sge::renderer::texture::mipmap::object const
	mipmap() const;

	void
	generate_mipmaps();
protected:
	sge::renderer::texture::mipmap::level_count const
	levels() const;
public:
	d3d_type &
	get() const;

	sge::image::color::format
	color_format() const;
protected:
	parameters_type const &
	parameters() const;
private:
	typedef typename Types::unique_ptr d3d_unique_ptr;

	d3d_unique_ptr
	create(
		D3DPOOL,
		sge::d3d9::usage
	) const;

	void
	init();

	void
	on_reset();

	void
	on_loss();

	IDirect3DDevice9 &device_;

	parameters_type const parameters_;

	sge::image::color::format const color_format_;

	D3DFORMAT const d3d_color_format_;

	sge::d3d9::usage const usage_;

	d3d_unique_ptr texture_;
};

}
}
}

#endif
