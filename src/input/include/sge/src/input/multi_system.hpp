/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#ifndef SGE_SRC_INPUT_MULTI_SYSTEM_HPP_INCLUDED
#define SGE_SRC_INPUT_MULTI_SYSTEM_HPP_INCLUDED

#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/plugin/manager_fwd.hpp>
#include <sge/plugin/object_shared_ptr.hpp>
#include <sge/src/input/system_ptr_vector.hpp>
#include <sge/window/object_fwd.hpp>
#include <sge/window/system_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace input
{

class multi_system
:
	public sge::input::system
{
	FCPPT_NONCOPYABLE(
		multi_system
	);
public:
	explicit
	multi_system(
		sge::plugin::manager &
	);

	~multi_system();
private:
	sge::input::processor_unique_ptr
	create_processor(
		sge::window::object const &,
		sge::window::system const &
	);

	typedef std::vector<
		sge::plugin::object_shared_ptr<
			sge::input::system
		>::type
	> plugin_vector;

	plugin_vector plugins_;

	sge::input::system_ptr_vector systems_;
};

}
}

#endif
