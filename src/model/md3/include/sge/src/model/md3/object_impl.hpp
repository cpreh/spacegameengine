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


#ifndef SGE_SRC_MODEL_MD3_OBJECT_IMPL_HPP_INCLUDED
#define SGE_SRC_MODEL_MD3_OBJECT_IMPL_HPP_INCLUDED

#include <sge/model/md3/index_sequence.hpp>
#include <sge/model/md3/load_flags.hpp>
#include <sge/model/md3/object.hpp>
#include <sge/model/md3/optional_normal_sequence.hpp>
#include <sge/model/md3/optional_texcoord_sequence.hpp>
#include <sge/model/md3/part_name_sequence.hpp>
#include <sge/model/md3/string.hpp>
#include <sge/model/md3/vertex_sequence.hpp>
#include <sge/src/model/md3/frame_vector.hpp>
#include <sge/src/model/md3/surface_vector.hpp>
#include <sge/src/model/md3/tag_vector.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace model
{
namespace md3
{

class object_impl
:
	public md3::object
{
	FCPPT_NONCOPYABLE(
		object_impl
	);
public:
	object_impl(
		std::istream &,
		md3::load_flags::type
	);

	~object_impl();

	md3::index_sequence const
	indices(
		md3::string const &
	) const;

	md3::vertex_sequence const
	vertices(
		md3::string const &
	) const;

	md3::optional_texcoord_sequence const
	texcoords(
		md3::string const &
	) const;

	md3::optional_normal_sequence const
	normals(
		md3::string const &
	) const;

	md3::part_name_sequence const
	part_names() const;
private:
	std::size_t
		vertices_,
		indices_;

	md3::string name_;

	md3::frame_vector frames_;

	md3::tag_vector tags_;

	md3::surface_vector surfaces_;

	md3::surface_vector::const_reference
	surface_by_name(
		md3::string const &
	) const;
};

}
}
}

#endif
