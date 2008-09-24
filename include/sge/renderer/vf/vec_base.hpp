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


#ifndef SGE_RENDERER_VF_VEC_BASE_HPP_INCLUDED
#define SGE_RENDERER_VF_VEC_BASE_HPP_INCLUDED

#include "vertex_size.hpp"
#include "element_base.hpp"
#include "../../math/vector.hpp"

namespace sge
{
namespace renderer
{
namespace vf
{

template<
	typename Format,
	vertex_size NumSubElements,
	vertex_size NumElements
>
struct vec_base : element_base<NumElements> {
	typedef Format subelement_type;
	typedef math::basic_vector<Format, NumSubElements> packet_type;
	static vertex_size const num_subelements = NumSubElements;
};


