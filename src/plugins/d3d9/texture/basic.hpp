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


#ifndef SGE_D3D9_TEXTURE_BASIC_HPP_INCLUDED
#define SGE_D3D9_TEXTURE_BASIC_HPP_INCLUDED

#include "basic_fwd.hpp"
#include "base.hpp"
#include "../d3d_device_ptr.hpp"
#include "../d3dinclude.hpp"
#include "../usage.hpp"
#include "../resource.hpp"
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/resource_flags_field.hpp>
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
	public d3d9::texture::base,
	public d3d9::resource
{
	FCPPT_NONCOPYABLE(
		basic
	);
public:
	typedef typename Types::parameters parameters_type;

	basic(
		d3d9::d3d_device_ptr,
		parameters_type const &
	);

	~basic();

	parameters_type const &
	parameters() const;
protected:
	d3d9::d3d_device_ptr const
	device() const;

	D3DPOOL
	pool() const;

	d3d9::usage const
	usage() const;

	sge::renderer::resource_flags_field const 
	resource_flags() const;

	sge::renderer::texture::capabilities_field const
	capabilities() const;

	void
	on_reset();

	void
	on_loss();
private:
	virtual IDirect3DBaseTexture9 *
	do_reset() = 0;

	virtual void
	do_loss() = 0;

	d3d9::d3d_device_ptr const device_;

	parameters_type const parameters_;
};

}
}
}

#endif
