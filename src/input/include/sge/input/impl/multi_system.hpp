/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2015 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#ifndef SGE_INPUT_IMPL_MULTI_SYSTEM_HPP_INCLUDED
#define SGE_INPUT_IMPL_MULTI_SYSTEM_HPP_INCLUDED

#include <sge/input/capabilities_field.hpp>
#include <sge/input/processor_unique_ptr.hpp>
#include <sge/input/system.hpp>
#include <sge/input/impl/system_ptr_vector.hpp>
#include <sge/input/plugin/collection_fwd.hpp>
#include <sge/input/plugin/object.hpp>
#include <sge/log/option_container.hpp>
#include <sge/plugin/manager_fwd.hpp>
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
namespace impl
{

class multi_system
:
	public sge::input::system
{
	FCPPT_NONCOPYABLE(
		multi_system
	);
public:
	multi_system(
		sge::input::plugin::collection const &,
		sge::log::option_container const &
	);

	~multi_system()
	override;
private:
	sge::input::processor_unique_ptr
	create_processor(
		sge::window::object const &,
		sge::window::system const &
	)
	override;

	sge::input::capabilities_field
	capabilities() const
	override;

	typedef
	std::vector<
		sge::input::plugin::object
	>
	plugin_vector;

	plugin_vector plugins_;

	sge::input::impl::system_ptr_vector systems_;

	sge::input::capabilities_field capabilities_;
};

}
}
}

#endif
