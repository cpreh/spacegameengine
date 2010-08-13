/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include "../set_filter.hpp"
#include "../parameter_int.hpp"
#include "../../texture_context.hpp"
#include "../../context/use.hpp"
#include "../../convert/texture_min_filter.hpp"
#include "../../convert/texture_mag_filter.hpp"
#include "../../common.hpp"
#include <sge/renderer/filter/texture.hpp>
#include <sge/log/global.hpp>
#include <sge/exception.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/text.hpp>

void
sge::opengl::texfuncs::set_filter(
	context::object &_context,
	GLenum const _type,
	renderer::filter::texture const &_filter
)
{
	texfuncs::parameter_int(
		_type,
		GL_TEXTURE_MIN_FILTER,
		convert::texture_min_filter(
			_filter.min()
		)
	);

	texfuncs::parameter_int(
		_type,
		GL_TEXTURE_MAG_FILTER,
		convert::texture_mag_filter(
			_filter.mag()
		)
	);

	if(
		!_filter.anisotropy()
	)
		return;

	texture_context const &context(
		opengl::context::use<
			texture_context
		>(
			_context
		)
	);
	
	if(
		!context.anisotropic_filter_supported()
	)
	{
		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("anisotropic filtering is not supported!")
		);

		return;
	}

	try
	{
		texfuncs::parameter_int(
			_type,
			context.anisotropy_flag(),
			_filter.anisotropy()
		);
	}
	catch(
		sge::exception const &
	)
	{
		FCPPT_LOG_ERROR(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("anisotropy level ")
				<< _filter.anisotropy()
				<< FCPPT_TEXT(" not supported!")
		);

		throw;
	}
}
