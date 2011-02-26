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


#include <sge/renderer/texture/filter/need_mipmap.hpp>
#include <sge/renderer/exception.hpp>
#include <fcppt/text.hpp>

bool
sge::renderer::texture::filter::need_mipmap(
	sge::renderer::texture::filter::min::type const _filter
)
{
	switch(
		_filter
	)
	{
	case sge::renderer::texture::filter::min::mipmap:
	case sge::renderer::texture::filter::min::trilinear:
		return true;
	case sge::renderer::texture::filter::min::point:
	case sge::renderer::texture::filter::min::linear:
		return false;
	}
	
	throw renderer::exception(
		FCPPT_TEXT("Invalid texture filter!")
	);
}
