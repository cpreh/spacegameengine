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


#ifndef SGE_RENDERER_TEXTURE_FILTER_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_FILTER_HPP_INCLUDED

#include <sge/renderer/anisotropy_type.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{

namespace min_filter
{
	enum type {
		point,
		linear,
		mipmap,
		trilinear
	};
}

namespace mag_filter
{
	enum type {
		point,
		linear
	};
}

struct texture_filter {
	SGE_SYMBOL texture_filter(
		renderer::min_filter::type min_filter,
		renderer::mag_filter::type mag_filter,
		anisotropy_type anisotropy_level = 0);
	
	SGE_SYMBOL renderer::min_filter::type min_filter() const;
	SGE_SYMBOL renderer::mag_filter::type mag_filter() const;
	SGE_SYMBOL anisotropy_type anisotropy() const;
private:
	renderer::min_filter::type  min_filter_;
	renderer::mag_filter::type  mag_filter_;
	anisotropy_type             anisotropy_;
};

SGE_SYMBOL extern texture_filter const
	linear_filter,
	point_filter,
	mip_filter,
	trilinear_filter;
}
}

#endif
