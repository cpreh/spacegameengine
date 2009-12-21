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


#ifndef SGE_RENDERER_DISPLAY_MODE_HPP_INCLUDED
#define SGE_RENDERER_DISPLAY_MODE_HPP_INCLUDED

#include <sge/renderer/display_mode_fwd.hpp>
#include <sge/renderer/bit_depth.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/renderer/refresh_rate.hpp>
#include <sge/symbol.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

namespace sge
{
namespace renderer
{

class display_mode
{
public:
	SGE_SYMBOL display_mode(
		screen_size const &,
		renderer::bit_depth::type,
		renderer::refresh_rate
	);

	SGE_SYMBOL screen_size const &
	size() const;

	SGE_SYMBOL renderer::bit_depth::type
	bit_depth() const;

	SGE_SYMBOL renderer::refresh_rate
	refresh_rate() const;
private:
	screen_size               size_;
	renderer::bit_depth::type bit_depth_;
	renderer::refresh_rate    refresh_rate_;
};

SGE_SYMBOL fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	display_mode const &
);

SGE_SYMBOL bool
operator== (
	display_mode const &,
	display_mode const &
);

SGE_SYMBOL bool
operator!= (
	display_mode const &,
	display_mode const &
);

}
}

#endif
