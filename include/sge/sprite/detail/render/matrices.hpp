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


#ifndef SGE_SPRITE_DETAIL_RENDER_MATRICES_HPP_INCLUDED
#define SGE_SPRITE_DETAIL_RENDER_MATRICES_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/sprite/set_matrices.hpp>
#include <sge/sprite/render/matrix_options.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/utility/enable_if.hpp>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace sprite
{
namespace detail
{
namespace render
{

template<
	sge::sprite::render::matrix_options::type Options
>
typename boost::enable_if_c<
	Options == sge::sprite::render::matrix_options::set,
	void
>::type
matrices(
	sge::renderer::device &_device
)
{
	sge::sprite::set_matrices(
		_device
	);
}

template<
	sge::sprite::render::matrix_options::type Options
>
typename boost::enable_if_c<
	Options == sge::sprite::render::matrix_options::nothing,
	void
>::type
matrices(
	sge::renderer::device &
)
{
}

}
}
}
}

#endif
