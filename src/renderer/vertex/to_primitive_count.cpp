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


#include <sge/renderer/exception.hpp>
#include <sge/renderer/primitive_count.hpp>
#include <sge/renderer/primitive_type.hpp>
#include <sge/renderer/vertex/count.hpp>
#include <sge/renderer/vertex/to_primitive_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::primitive_count const
sge::renderer::vertex::to_primitive_count(
	sge::renderer::vertex::count const _vertex_count,
	sge::renderer::primitive_type const _primitive_type
)
{
	switch(
		_primitive_type
	)
	{
	case sge::renderer::primitive_type::point_list:
		return
			sge::renderer::primitive_count(
				_vertex_count.get()
			);
	case sge::renderer::primitive_type::line_list:
		if(
			_vertex_count.get() % 2u
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): line needs a multiple of two vertices!")
			);

		return
			sge::renderer::primitive_count(
				_vertex_count.get() / 2u
			);

	case sge::renderer::primitive_type::line_strip:
		if(
			_vertex_count.get() <= 1u
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): line_strip needs at least two vertices!")
			);

		return
			sge::renderer::primitive_count(
				_vertex_count.get() - 1u
			);
	case sge::renderer::primitive_type::triangle_strip:
	case sge::renderer::primitive_type::triangle_fan:
		if(
			_vertex_count.get() <= 2u
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): triangle_fan and triangle_strip need at least three vertices!")
			);

		return
			sge::renderer::primitive_count(
				_vertex_count.get() - 2u
			);
	case sge::renderer::primitive_type::triangle_list:
		if(
			_vertex_count.get() % 3u
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): triangle needs a multiple of three vertices!")
			);

		return
			sge::renderer::primitive_count(
				_vertex_count.get() / 3u
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
