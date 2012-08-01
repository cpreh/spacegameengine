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


#ifndef SGE_MODEL_OBJ_INDEX_BUFFER_RANGE_HPP_INCLUDED
#define SGE_MODEL_OBJ_INDEX_BUFFER_RANGE_HPP_INCLUDED

#include <sge/model/obj/symbol.hpp>
#include <sge/renderer/first_index.hpp>
#include <sge/renderer/index_count.hpp>

namespace sge
{
namespace model
{
namespace obj
{
class index_buffer_range
{
public:
	SGE_MODEL_OBJ_SYMBOL
	index_buffer_range(
		sge::renderer::first_index const &,
		sge::renderer::index_count const &);

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::first_index const &
	first_index() const;

	SGE_MODEL_OBJ_SYMBOL
	sge::renderer::index_count const &
	index_count() const;
private:
	sge::renderer::first_index first_index_;
	sge::renderer::index_count index_count_;
};
}
}
}

#endif
