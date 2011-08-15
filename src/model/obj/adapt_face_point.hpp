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


#ifndef SGE_MODEL_OBJ_ADAPT_FACE_POINT_HPP_INCLUDED
#define SGE_MODEL_OBJ_ADAPT_FACE_POINT_HPP_INCLUDED

#include <sge/model/obj/face_point.hpp>
#include <sge/model/obj/index.hpp>
#include <sge/model/obj/optional_index.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
	sge::model::obj::face_point,
	(sge::model::obj::index, vertex_index_)
	(sge::model::obj::optional_index, texcoord_index_)
	(sge::model::obj::optional_index, normal_index_)
)

#endif
