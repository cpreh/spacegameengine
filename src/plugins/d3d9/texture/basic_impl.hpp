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


#ifndef SGE_D3D9_BASIC_TEXTURE_IMPL_HPP_INCLUDED
#define SGE_D3D9_BASIC_TEXTURE_IMPL_HPP_INCLUDED

template<typename Base>
sge::d3d9::basic_texture<Base>::basic_texture(renderer& rend,
                                              const filter_args& filter_,
                                              const resource_flag_t flags_)
 : texture_base(0),
   resource(rend, flags_),
   filter_(filter_),
   flags_(flags_)
{}

template<typename Base>
const sge::filter_args& sge::d3d9::basic_texture<Base>::filter() const
{
	return filter_;
}

template<
	typename Base
>
void sge::d3d9::basic_texture<Base>::on_reset()
{
	base(do_reset());
}

template<
	typename Base
>
void sge::d3d9::basic_texture<Base>::on_loss()
{
	do_loss();
	base(0);
}

template<typename Base>
sge::resource_flag_t sge::d3d9::basic_texture<Base>::flags() const
{
	return flags_;
}

#endif
