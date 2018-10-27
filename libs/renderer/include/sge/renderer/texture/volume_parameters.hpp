/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_RENDERER_TEXTURE_VOLUME_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_TEXTURE_VOLUME_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/dim3.hpp>
#include <sge/renderer/texture/detail/declare_basic_parameters.hpp>
#include <sge/renderer/texture/color_format.hpp>
#include <sge/renderer/texture/volume_parameters_fwd.hpp>


SGE_RENDERER_TEXTURE_DETAIL_DECLARE_BASIC_PARAMETERS(
	sge::renderer::dim3,
	sge::renderer::texture::color_format
);

#endif
