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


#ifndef SGE_RENDERER_TEXTURE_FILTER_OBJECT_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_FILTER_OBJECT_HPP_INCLUDED

#include <sge/renderer/texture/filter/object_fwd.hpp>
#include <sge/renderer/texture/filter/min.hpp>
#include <sge/renderer/texture/filter/mag.hpp>
#include <sge/renderer/texture/filter/anisotropy_type.hpp>
#include <sge/renderer/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace texture
{
namespace filter
{

class object
{
public:
	SGE_RENDERER_SYMBOL
	object(
		filter::min::type,
		filter::mag::type,
		filter::anisotropy_type
	);

	SGE_RENDERER_SYMBOL
	filter::min::type
	min() const;

	SGE_RENDERER_SYMBOL
	filter::mag::type
	mag() const;

	SGE_RENDERER_SYMBOL
	filter::anisotropy_type const
	anisotropy() const;
private:
	filter::min::type min_;

	filter::mag::type mag_;

	filter::anisotropy_type anisotropy_;
};

}
}
}
}

#endif
