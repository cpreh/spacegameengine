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


#ifndef SGE_RENDERER_PARAMETERS_HPP_INCLUDED
#define SGE_RENDERER_PARAMETERS_HPP_INCLUDED

#include <sge/renderer/parameters_fwd.hpp>
#include <sge/renderer/depth_stencil_buffer.hpp>
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/multi_sample_type.hpp>
#include <sge/renderer/screen_mode.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/symbol.hpp>
#include <fcppt/variant/object_impl.hpp>

namespace sge
{
namespace renderer
{

class parameters
{
public:
	SGE_SYMBOL parameters(
		renderer::screen_mode const &,
		renderer::depth_stencil_buffer::type,
		renderer::vsync::type,
		renderer::multi_sample_type
	);

	SGE_SYMBOL
	renderer::screen_mode const &
	screen_mode() const;

	SGE_SYMBOL
	renderer::depth_stencil_buffer::type
	depth_stencil_buffer() const;

	SGE_SYMBOL
	renderer::vsync::type
	vsync() const;

	SGE_SYMBOL
	renderer::multi_sample_type
	samples() const;
private:
	renderer::screen_mode screen_mode_;

	renderer::depth_stencil_buffer::type depth_stencil_buffer_;

	renderer::vsync::type vsync_;

	renderer::multi_sample_type samples_;
};

}
}

#endif
