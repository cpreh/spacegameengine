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


#include "../create_mipmap.hpp"
#include "../auto_generate_mipmap.hpp"
#include "../parameter_int.hpp"
#include "../../context.hpp"
#include "../../../context/use.hpp"
#include "../../../common.hpp"
#include <sge/renderer/texture/mipmap/object.hpp>

void
sge::opengl::texture::funcs::create_mipmap(
	texture::scoped_work_bind const &_scoped_work,
	opengl::context::object &_context,
	texture::type const _type,
	renderer::texture::mipmap::object const &_mipmap
)
{
#if 0
		opengl::texture::funcs::auto_generate_mipmap(
			_scoped_work,
			_context,
			_type
		);

	if(
		_filter.anisotropy().get() == 0u
	)
		return;

	texture::context const &context(
		opengl::context::use<
			texture::context
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

#endif
}
