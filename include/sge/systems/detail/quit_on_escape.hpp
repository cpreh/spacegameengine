/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_SYSTEMS_DETAIL_QUIT_ON_ESCAPE_HPP_INCLUDED
#define SGE_SYSTEMS_DETAIL_QUIT_ON_ESCAPE_HPP_INCLUDED

#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/systems/detail/symbol.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>


namespace sge
{
namespace systems
{
namespace detail
{

SGE_SYSTEMS_DETAIL_SYMBOL
fcppt::signal::auto_connection
quit_on_escape(
	sge::input::keyboard::device &,
	sge::window::system &
);

}
}
}

#endif
