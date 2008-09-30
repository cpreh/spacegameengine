/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2007  Carl Philipp Reh (sefi@s-e-f-i.de)

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

#include "display_mode.hpp"
#include "multi_sampling.hpp"
#include "depth_buffer.hpp"
#include "stencil_buffer.hpp"
#include "window_mode.hpp"
#include "vsync.hpp"
#include "../export.hpp"

namespace sge
{
namespace renderer
{

struct parameters {
	SGE_SYMBOL parameters(
		display_mode const &mode,
		depth_buffer::type,
		stencil_buffer::type,
		window_mode::type,
		vsync::type = vsync::on,
		multi_sample_type samples = 1);

	SGE_SYMBOL display_mode const &mode() const;
	SGE_SYMBOL depth_buffer::type dbuffer() const;
	SGE_SYMBOL stencil_buffer::type sbuffer() const;
	SGE_SYMBOL window_mode::type wmode() const;
	SGE_SYMBOL vsync::type vsmode() const;
	SGE_SYMBOL multi_sample_type samples() const;
private:
	display_mode         mode_;
	depth_buffer::type   depth_buffer_;
	stencil_buffer::type stencil_buffer_;
	window_mode::type    window_mode_;
	vsync::type          vsync_;
	multi_sample_type    samples_;
};

}
}

#endif
