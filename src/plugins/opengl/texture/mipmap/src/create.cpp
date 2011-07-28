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


#include "../create.hpp"
#include "../visitor.hpp"
#include "../../instantiate_dim.hpp"
#include <sge/renderer/texture/mipmap/object.hpp>
#include <fcppt/variant/apply_unary.hpp>
#include <fcppt/variant/object_impl.hpp>

template<
	fcppt::math::size_type Dim
>
void
sge::opengl::texture::mipmap::create(
	mipmap::parameters<
		Dim
	> const &_parameters,
	renderer::texture::mipmap::object const &_mipmap
)
{
	fcppt::variant::apply_unary(
		mipmap::visitor<
			Dim
		>(
			_parameters
		),
		_mipmap.variant()
	);
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

#define SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_CREATE(\
	dimension\
)\
template \
void \
sge::opengl::texture::mipmap::create<\
	dimension\
>(\
	sge::opengl::texture::mipmap::parameters< \
		dimension \
	> const &, \
	sge::renderer::texture::mipmap::object const &\
);

SGE_OPENGL_TEXTURE_INSTANTIATE_DIM(
	SGE_OPENGL_TEXTURE_MIPMAP_INSTANTIATE_CREATE
)
