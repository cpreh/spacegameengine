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


#ifndef SGE_GUI_EVENTS_KEY_HPP_INCLUDED
#define SGE_GUI_EVENTS_KEY_HPP_INCLUDED

#include <sge/input/key_pair.hpp>
#include <sge/input/modifier/states.hpp>
#include <sge/gui/export.hpp>
#include <fcppt/container/map_decl.hpp>

namespace sge
{
namespace gui
{
namespace events
{
class key
{
	public:
	SGE_GUI_SYMBOL key(
		input::key_pair const &,
		input::modifier::states const &,
		bool repeated);

	SGE_GUI_SYMBOL input::key_pair const &value() const;
	SGE_GUI_SYMBOL input::modifier::states const &modifiers() const;
	SGE_GUI_SYMBOL bool repeated() const;
	private:
	input::key_pair const kp;
	input::modifier::states const s;
	bool repeated_;
};
}
}
}

#endif
