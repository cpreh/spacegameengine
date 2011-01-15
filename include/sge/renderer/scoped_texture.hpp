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


#ifndef SGE_RENDERER_SCOPED_TEXTURE_HPP_INCLUDED
#define SGE_RENDERER_SCOPED_TEXTURE_HPP_INCLUDED

#include <sge/renderer/device_ptr.hpp>
#include <sge/renderer/const_texture_base_ptr.hpp>
#include <sge/renderer/stage_type.hpp>
#include <sge/symbol.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace renderer
{

class scoped_texture
{
	FCPPT_NONCOPYABLE(scoped_texture)
public:
	SGE_SYMBOL
	explicit scoped_texture(
		renderer::device_ptr,
		renderer::const_texture_base_ptr,
		renderer::stage_type = 0
	);

	SGE_SYMBOL
	~scoped_texture();
private:
	renderer::device_ptr const rend_;

	renderer::stage_type const stage_;
};

}
}

#endif
