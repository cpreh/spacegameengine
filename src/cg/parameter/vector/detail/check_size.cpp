/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/vector/detail/check_size.hpp>
#include <sge/src/cg/parameter/vector/element_count.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/size_type.hpp>


void
sge::cg::parameter::vector::detail::check_size(
	sge::cg::parameter::object const &_parameter,
	fcppt::math::size_type const _size
)
{
	FCPPT_ASSERT_ERROR(
		sge::cg::parameter::vector::element_count(
			_parameter
		)
		==
		_size
	);
}
