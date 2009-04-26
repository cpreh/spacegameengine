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



#ifndef SGE_RENDERER_FILTER_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_FILTER_TEXTURE_HPP_INCLUDED

#include <sge/renderer/filter/min.hpp>
#include <sge/renderer/filter/mag.hpp>
#include <sge/renderer/filter/anisotropy_type.hpp>
#include <sge/export.hpp>

namespace sge
{
namespace renderer
{
namespace filter
{

class texture {
public:
	SGE_SYMBOL texture(
		filter::min::type,
		filter::mag::type,
		anisotropy_type anisotropy_level = 0);
	
	SGE_SYMBOL filter::min::type min() const;
	SGE_SYMBOL filter::mag::type mag() const;
	SGE_SYMBOL anisotropy_type anisotropy() const;
private:
	filter::min::type  min_;
	filter::mag::type  mag_;
	anisotropy_type    anisotropy_;
};

}
}
}

#endif
