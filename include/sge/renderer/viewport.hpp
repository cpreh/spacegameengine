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


#ifndef SGE_RENDERER_VIEWPORT_HPP_INCLUDED
#define SGE_RENDERER_VIEWPORT_HPP_INCLUDED

#include "pixel_pos_t.hpp"
#include "screen_size_t.hpp"
#include "../export.hpp"
#include "../ostream.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

namespace sge
{
namespace renderer
{

class viewport {
public:
	SGE_SYMBOL viewport(
		pixel_pos_t const &,
		screen_size_t const &);

	SGE_SYMBOL pixel_pos_t const &pos() const;
	SGE_SYMBOL screen_size_t const &size() const;
private:
	pixel_pos_t   pos_;
	screen_size_t size_;
};

SGE_SYMBOL ostream &
operator<<(
	ostream &,
	viewport const &);

}
}

#endif
