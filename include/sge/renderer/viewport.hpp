/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2010 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_RENDERER_VIEWPORT_HPP_INCLUDED
#define SGE_RENDERER_VIEWPORT_HPP_INCLUDED

#include <sge/renderer/viewport_fwd.hpp>
#include <sge/renderer/pixel_pos.hpp>
#include <sge/renderer/screen_size.hpp>
#include <sge/symbol.hpp>
#include <fcppt/io/ostream.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

namespace sge
{
namespace renderer
{

class viewport
{
public:
	SGE_SYMBOL viewport(
		pixel_pos const &,
		screen_size const &
	);

	SGE_SYMBOL pixel_pos const &
	pos() const;

	SGE_SYMBOL screen_size const &
	size() const;
private:
	pixel_pos   pos_;
	screen_size size_;
};

SGE_SYMBOL fcppt::io::ostream &
operator<<(
	fcppt::io::ostream &,
	viewport const &
);

}
}

#endif
