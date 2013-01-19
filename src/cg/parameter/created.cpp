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


#include <sge/cg/check_state.hpp>
#include <sge/cg/exception.hpp>
#include <sge/cg/context/object.hpp>
#include <sge/cg/parameter/created.hpp>
#include <sge/cg/parameter/element_type.hpp>
#include <sge/cg/parameter/named.hpp>
#include <sge/cg/parameter/object.hpp>
#include <sge/src/cg/parameter/convert_element_type.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


sge::cg::parameter::created::created(
	sge::cg::context::object const &_context,
	sge::cg::parameter::element_type const _element_type
)
:
	parameter_(
		::cgCreateParameter(
			_context.get(),
			sge::cg::parameter::convert_element_type(
				_element_type
			)
		)
	)
{
	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgCreateParameter failed"),
		sge::cg::exception
	)
}

sge::cg::parameter::created::~created()
{
	::cgDestroyParameter(
		parameter_
	);
}

sge::cg::parameter::object const
sge::cg::parameter::created::object() const
{
	return
		sge::cg::parameter::object(
			parameter_
		);
}

void
sge::cg::parameter::created::connect(
	sge::cg::parameter::named const &_named
)
{
	::cgConnectParameter(
		parameter_,
		_named.object().get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgConnectParameter failed"),
		sge::cg::exception
	)
}

void
sge::cg::parameter::created::disconnect(
	sge::cg::parameter::named const &_named
)
{
	::cgDisconnectParameter(
		_named.object().get()
	);

	SGE_CG_CHECK_STATE(
		FCPPT_TEXT("cgDisconnectParameter failed"),
		sge::cg::exception
	)
}
