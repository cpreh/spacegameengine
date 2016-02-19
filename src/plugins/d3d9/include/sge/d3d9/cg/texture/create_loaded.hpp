/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_D3D9_CG_TEXTURE_CREATE_LOADED_HPP_INCLUDED
#define SGE_D3D9_CG_TEXTURE_CREATE_LOADED_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/d3d9/d3dinclude.hpp>
#include <sge/renderer/caps/texture_stages.hpp>
#include <sge/renderer/cg/loaded_texture_unique_ptr.hpp>
#include <sge/renderer/texture/base_fwd.hpp>


namespace sge
{
namespace d3d9
{
namespace cg
{
namespace texture
{

sge::renderer::cg::loaded_texture_unique_ptr
create_loaded(
	IDirect3DDevice9 &,
	sge::cg::parameter::object const &,
	sge::renderer::texture::base &,
	sge::renderer::caps::texture_stages
);

}
}
}
}

#endif
