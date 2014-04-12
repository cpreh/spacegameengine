/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2013 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_SYSTEMS_MODULES_WINDOW_SYSTEM_HPP_INCLUDED
#define SGE_SRC_SYSTEMS_MODULES_WINDOW_SYSTEM_HPP_INCLUDED

#include <sge/src/systems/modules/window/system_base_unique_ptr.hpp>
#include <sge/src/systems/modules/window/system_fwd.hpp>
#include <sge/systems/window_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace systems
{
namespace modules
{
namespace window
{

class system
{
	FCPPT_NONCOPYABLE(
		system
	);
public:
	explicit
	system(
		sge::systems::window const &
	);

	~system();

	sge::window::system &
	get() const;
private:
	sge::systems::modules::window::system_base_unique_ptr const base_;
};

}
}
}
}

#endif
