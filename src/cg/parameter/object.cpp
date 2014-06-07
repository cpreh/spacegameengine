/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2014 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/cg/parameter/object.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


sge::cg::parameter::object::object(
	CGparameter const _parameter
)
:
	parameter_(
		_parameter
	)
{
	FCPPT_ASSERT_PRE(
		parameter_
		!=
		nullptr
	);
}

sge::cg::parameter::object::object(
	sge::cg::parameter::object const &_other
)
:
	parameter_(
		_other.parameter_
	)
{
}

sge::cg::parameter::object::~object()
{
}

CGparameter
sge::cg::parameter::object::get() const
{
	return
		parameter_;
}
