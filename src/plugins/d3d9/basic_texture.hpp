/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_D3D9_BASIC_TEXTURE_HPP_INCLUDED
#define SGE_D3D9_BASIC_TEXTURE_HPP_INCLUDED

#include "texture_base.hpp"
#include "resource.hpp"
#include "d3dinclude.hpp"
#include <sge/renderer/texture_filter.hpp>
#include <sge/renderer/types.hpp>

namespace sge
{
namespace d3d9
{

class renderer;

template<typename Base>
class basic_texture : public Base, public texture_base, public resource {
public:
	basic_texture(renderer&, const filter_args& filter, resource_flag_t flags);
protected:
	resource_flag_t flags() const;
	void on_reset();
	void on_loss();
private:
	void filter(const filter_args&);

	virtual IDirect3DBaseTexture9* do_reset() = 0;
	virtual void do_loss() = 0;

	filter_args     filter_;
	resource_flag_t flags_;
};

}
}

#endif
