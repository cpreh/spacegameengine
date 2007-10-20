/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

namespace sge
{
namespace d3d9
{

template<typename Base>
class basic_texture : public Base, public resource {
public:
	basic_texture(IDirect3DBaseTexture9*, renderer&, const filter_args& filter, resource_flag_t flags);
	const filter_args& filter() const;
protected:
	void reset();
private:
	void filter(const filter_args&);
	resource_flag_t flags() const;

	void on_loss();
	virtual void on_reset() = 0;

	filter_args my_filter;
};

}
}

#endif
