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
#include <sge/renderer/display_mode.hpp>
#include <sge/renderer/multi_sample_type.hpp>
#include <sge/renderer/depth_buffer.hpp>
#include <sge/renderer/stencil_buffer.hpp>
#include <sge/renderer/window_mode.hpp>
#include <sge/renderer/vsync.hpp>
#include <sge/symbol.hpp>

namespace sge
{
namespace renderer
{

class parameters
{
public:
	SGE_SYMBOL parameters(
		renderer::display_mode const &,
		renderer::depth_buffer::type,
		renderer::stencil_buffer::type,
		renderer::window_mode::type,
		renderer::vsync::type,
		renderer::multi_sample_type
	);

	SGE_SYMBOL
	renderer::display_mode const &
	display_mode() const;

	SGE_SYMBOL
	renderer::depth_buffer::type
	depth_buffer() const;

	SGE_SYMBOL
	renderer::stencil_buffer::type
	stencil_buffer() const;

	SGE_SYMBOL
	renderer::window_mode::type
	window_mode() const;

	SGE_SYMBOL
	renderer::vsync::type
	vsync() const;

	SGE_SYMBOL
	renderer::multi_sample_type
	samples() const;
private:
	renderer::display_mode         mode_;
	renderer::depth_buffer::type   depth_buffer_;
	renderer::stencil_buffer::type stencil_buffer_;
	renderer::window_mode::type    window_mode_;
	renderer::vsync::type          vsync_;
	renderer::multi_sample_type    samples_;
};

}
}

#endif
