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



#ifndef SGE_TEXTURE_ATLASING_HPP_INCLUDED
#define SGE_TEXTURE_ATLASING_HPP_INCLUDED

#include <sge/renderer/texture_fwd.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/dim_type.hpp>
#include <sge/renderer/lock_rect.hpp>
#include <sge/image/view/const_object.hpp>
#include <sge/image/color/format.hpp>

namespace sge
{
namespace renderer
{
namespace filter
{
class texture;
}
}

namespace texture
{

bool need_atlasing(
	renderer::size_type);

bool need_atlasing(
	renderer::dim_type const &);

renderer::size_type
atlased_bound(
	renderer::size_type);

renderer::dim_type const
atlased_bounds(
	renderer::dim_type const &);

renderer::size_type atlased_gap();

renderer::size_type
atlased_size(
	renderer::size_type,
	bool force_atlasing = false);

renderer::dim_type const
atlased_size(
	renderer::dim_type const &,
	bool force_atlasing = false);

renderer::dim_type const
atlased_texture_dim(
	renderer::device_ptr rend);

renderer::texture_ptr const
atlased_texture(
	renderer::device_ptr rend,
	image::color::format::type,
	renderer::filter::texture const &filter);

renderer::lock_rect const
inner_atlased_rect(
	renderer::lock_rect,
	bool need_atlasing_w,
	bool need_atlasing_h);

void atlas_w(
	renderer::texture_ptr,
	image::view::const_object const &src,
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area);
	
void atlas_h(
	renderer::texture_ptr,
	image::view::const_object const &src,
	renderer::lock_rect const &outer_area,
	renderer::lock_rect const &inner_area);
}
}

#endif
