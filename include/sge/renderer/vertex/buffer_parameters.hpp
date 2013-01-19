/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VERTEX_BUFFER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_VERTEX_BUFFER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/symbol.hpp>
#include <sge/renderer/vertex/buffer_parameters_fwd.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/renderer/vf/dynamic/part_index.hpp>
#include <fcppt/nonassignable.hpp>


namespace sge
{
namespace renderer
{
namespace vertex
{

class buffer_parameters
{
	FCPPT_NONASSIGNABLE(
		buffer_parameters
	);
public:
	/**
	\brief Describes a vertex buffer.

	It will be able to hold \a count vertices. \a flags describes the
	capabilities of the buffer. Initially, the contents of the buffer are
	undefined.

	\param declaration The vertex declaration the buffer belongs to

	\param part The part of the vertex declaration the buffer will be
	holding vertices for

	\param count The number of vertices the buffer will hold

	\param flags The capabilitiies of the buffer
	*/
	SGE_RENDERER_SYMBOL
	buffer_parameters(
		sge::renderer::vertex::declaration const &declaration,
		sge::renderer::vf::dynamic::part_index part,
		sge::renderer::vertex::count count,
		sge::renderer::resource_flags_field const &flags
	);

	SGE_RENDERER_SYMBOL
	sge::renderer::vertex::declaration const &
	declaration() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::vf::dynamic::part_index const
	part() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::vertex::count const
	count() const;

	SGE_RENDERER_SYMBOL
	sge::renderer::resource_flags_field const &
	flags() const;
private:
	sge::renderer::vertex::declaration const &declaration_;

	sge::renderer::vf::dynamic::part_index const part_;

	sge::renderer::vertex::count const count_;

	sge::renderer::resource_flags_field const flags_;
};

}
}
}

#endif
