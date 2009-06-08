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


#ifndef SGE_GUI_KEY_HANDLING_HPP_INCLUDED
#define SGE_GUI_KEY_HANDLING_HPP_INCLUDED

// This is the return value of the process(key) event and determines if the gui
// should process the key after the widget got it. For example, a widget could
// decide to completely ignore the key (like a button ignores the "tab" key, so
// the manager uses it to cycle the keyboard focus), it could process the key
// and don't let the manager do anything with it (widgets::edit probably wants
// to process the tab key and display a tab character), or it could process the
// key and then hand it over to the manager.

namespace sge
{
namespace gui
{
namespace key_handling
{
enum type 
{ 
	process,
	ignore 
};
}
}
}

#endif
