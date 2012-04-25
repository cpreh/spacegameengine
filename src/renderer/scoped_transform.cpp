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


#include <sge/renderer/matrix4.hpp>
#include <sge/renderer/matrix_mode.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/scoped_transform.hpp>
#include <fcppt/math/matrix/object_impl.hpp>


sge::renderer::scoped_transform::scoped_transform(
	sge::renderer::context::object &_context,
	sge::renderer::matrix_mode::type const _mode,
	sge::renderer::matrix4 const &_new_matrix
)
:
	context_(
		_context
	),
	mode_(
		_mode
	)
{
	context_.transform(
		_mode,
		_new_matrix
	);
}

sge::renderer::scoped_transform::~scoped_transform()
{
	context_.transform(
		mode_,
		sge::renderer::matrix4::identity()
	);
}
