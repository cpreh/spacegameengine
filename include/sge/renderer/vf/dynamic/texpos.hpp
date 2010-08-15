/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VF_DYNAMIC_TEXPOS_HPP_INCLUDED
#define SGE_RENDERER_VF_DYNAMIC_TEXPOS_HPP_INCLUDED

#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector.hpp>
#include <sge/renderer/vf/vertex_size.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{
namespace vf
{
namespace dynamic
{

class texpos
{
public:
	SGE_SYMBOL explicit texpos(
		vector const &,
		vf::vertex_size index
	);

	SGE_SYMBOL
	vector const &
	type() const;

	SGE_SYMBOL
	vf::vertex_size
	index() const;
private:
	vector type_;

	vf::vertex_size index_;
};

}
}
}
}

#endif
