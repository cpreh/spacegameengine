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


#include <sge/renderer/system.hpp>
#include <sge/renderer/caps/system_field.hpp>
#include <sge/renderer/plugin/collection_fwd.hpp>
#include <sge/renderer/plugin/traits.hpp>
#include <sge/src/systems/find_plugin.hpp>
#include <sge/src/systems/modules/renderer/find_plugin.hpp>
#include <sge/src/systems/modules/renderer/system_pair.hpp>
#include <sge/systems/optional_name.hpp>
#include <fcppt/container/bitfield/is_subset_eq.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/spirit/home/phoenix/bind/bind_function.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <boost/spirit/home/phoenix/core/argument.hpp>
#include <fcppt/config/external_end.hpp>



sge::systems::modules::renderer::system_pair const
sge::systems::modules::renderer::find_plugin(
	sge::renderer::plugin::collection const &_collection,
	sge::systems::optional_name const &_name,
	sge::renderer::caps::system_field const &_caps
)
{
	return
		sge::systems::find_plugin<
			sge::renderer::system
		>(
			_collection,
			_name,
			boost::phoenix::bind(
				&fcppt::container::bitfield::is_subset_eq<
					sge::renderer::caps::system_field::enum_type,
					sge::renderer::caps::system_field::static_size::value,
					sge::renderer::caps::system_field::internal_type
				>,
				_caps,
				boost::phoenix::bind(
					&sge::renderer::system::caps,
					boost::phoenix::arg_names::arg1
				)
			)
		);
}
