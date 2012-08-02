/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include <sge/model/obj/box.hpp>
#include <sge/model/obj/material_to_index_buffer_range.hpp>
#include <sge/model/obj/prototype.hpp>
#include <sge/model/obj/symbol.hpp>
#include <sge/renderer/device_fwd.hpp>
#include <sge/renderer/index_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_buffer_scoped_ptr.hpp>
#include <sge/renderer/vertex_declaration_fwd.hpp>
#include <fcppt/math/box/object_impl.hpp>


namespace sge
{
namespace model
{
namespace obj
{
class instance
{
FCPPT_NONCOPYABLE(
	instance);
public:
	SGE_MODEL_OBJ_SYMBOL
	explicit
	instance(
		sge::renderer::device &,
		sge::renderer::vertex_declaration &,
		sge::model::obj::prototype const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::vertex_buffer &
	vertex_buffer();

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::index_buffer &
	index_buffer();

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::material_to_index_buffer_range const &
	parts();

	SGE_MODEL_OBJ_SYMBOL
	sge::model::obj::box const &
	bounding_box() const;

	SGE_MODEL_OBJ_SYMBOL
	~instance();
private:
	sge::renderer::vertex_buffer_scoped_ptr vertex_buffer_;
	sge::renderer::index_buffer_scoped_ptr index_buffer_;
	sge::model::obj::material_to_index_buffer_range parts_;
	sge::model::obj::box bounding_box_;

	void
	fill_vertex_buffer(
		sge::model::obj::prototype const &);

	void
	fill_index_buffer(
		sge::model::obj::prototype const &);
};
}
}
}

#endif
