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


#ifndef SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED
#define SGE_OPENGL_VERTEX_DECLARATION_HPP_INCLUDED

#include <sge/opengl/vertex_declaration_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/vf/attribute_location_container.hpp>
#include <sge/opengl/vf/part_fwd.hpp>
#include <sge/renderer/vertex_declaration.hpp>
#include <sge/renderer/vf/dynamic/format.hpp>
#include <sge/renderer/vf/dynamic/part_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace opengl
{

class vertex_declaration
:
	public sge::renderer::vertex_declaration
{
	FCPPT_NONCOPYABLE(
		vertex_declaration
	);
public:
	vertex_declaration(
		opengl::context::object &,
		renderer::vf::dynamic::format const &
	);

	~vertex_declaration();

	sge::renderer::vf::dynamic::part const &
	format_part(
		sge::renderer::vf::dynamic::part_index
	) const;

	opengl::vf::part const &
	gl_format_part(
		sge::renderer::vf::dynamic::part_index
	) const;

	opengl::vf::attribute_location_container const &
	attribute_locations() const;
private:
	sge::renderer::vf::dynamic::format const format_;

	typedef boost::ptr_vector<
		opengl::vf::part
	> part_vector;

	part_vector parts_;

	opengl::vf::attribute_location_container attribute_locations_;
};

}
}

#endif
