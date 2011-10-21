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


#ifndef SGE_MODEL_OBJ_INSTANCE_HPP_INCLUDED
#define SGE_MODEL_OBJ_INSTANCE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/model/obj/instance_fwd.hpp>
#include <sge/model/obj/mesh_sequence.hpp>
#include <sge/model/obj/normal_sequence.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/model/obj/texcoord_sequence.hpp>
#include <sge/model/obj/vertex_sequence.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace model
{
namespace obj
{
/**
	The object loader does NOT support the following:

	- Smoothing groups: too complex to implement, requires multiple
	passes over the input
	- Materials: too complex to parse, see the spec here: http://paulbourke.net/dataformats/mtl/
	- Point primitives: too irrelevant
	- Curves: too complex, too irrelevant
 */
class SGE_CLASS_SYMBOL instance
{
	FCPPT_NONCOPYABLE(
		instance
	);
protected:
	instance();
public:
	virtual obj::vertex_sequence const &
	vertices() const = 0;

	virtual obj::texcoord_sequence const &
	texcoords() const = 0;

	virtual obj::normal_sequence const &
	normals() const = 0;

	virtual obj::mesh_sequence const &
	meshes() const = 0;

	SGE_MODEL_OBJ_SYMBOL
	virtual ~instance() = 0;
};

}
}
}

#endif
