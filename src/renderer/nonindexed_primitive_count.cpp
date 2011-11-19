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


#include <sge/renderer/exception.hpp>
#include <sge/renderer/nonindexed_primitive_count.hpp>
#include <sge/renderer/nonindexed_primitive_type.hpp>
#include <sge/renderer/size_type.hpp>
#include <sge/renderer/vertex_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/unreachable.hpp>


sge::renderer::size_type
sge::renderer::nonindexed_primitive_count(
	renderer::vertex_count const _vertex_count,
	renderer::nonindexed_primitive_type::type const _primitive_type
)
{
	switch(
		_primitive_type
	)
	{
	case nonindexed_primitive_type::point:
		return _vertex_count.get();
	case nonindexed_primitive_type::line:
		if(
			_vertex_count.get() % 2
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): line needs a multiple of two vertices!")
			);

		return _vertex_count.get() / 2;

	case nonindexed_primitive_type::line_strip:
		if(
			_vertex_count.get() <= 1
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): line_strip needs at least two vertices!")
			);

		return _vertex_count.get() - 1;
	case nonindexed_primitive_type::triangle_strip:
	case nonindexed_primitive_type::triangle_fan:
		if(
			_vertex_count.get() <= 2
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): triangle_fan and triangle_strip need at least three vertices!")
			);

		return _vertex_count.get() - 2;
	case nonindexed_primitive_type::triangle:
		if(
			_vertex_count.get() % 3
		)
			throw sge::renderer::exception(
				FCPPT_TEXT("nonindexed_primitive_count(): triangle needs a multiple of three vertices!")
			);

		return _vertex_count.get() / 3;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
