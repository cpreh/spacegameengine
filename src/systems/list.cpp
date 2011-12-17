/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/log/global.hpp>
#include <sge/src/systems/make_any_key.hpp>
#include <sge/systems/any.hpp>
#include <sge/systems/any_map.hpp>
#include <sge/systems/list.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

bool
insert_to_map(
	sge::systems::any_map &_map,
	sge::systems::any const &_any
)
{
	return
		_map.insert(
			std::make_pair(
				sge::systems::make_any_key(
					_any
				),
				_any
			)
		).second;

}

}

sge::systems::list::list()
:
	states_()
{
}

sge::systems::list::list(
	sge::systems::any const &_any
)
:
	states_()
{
	::insert_to_map(
		states_,
		_any
	);
}

sge::systems::list const
sge::systems::list::operator()(
	sge::systems::any const &_any
) const
{
	sge::systems::list ret(
		*this
	);

	if(
		!::insert_to_map(
			ret.states_,
			_any
		)
	)
	{
		FCPPT_LOG_WARNING(
			sge::log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Duplicate system state given!")
		);
	}

	return ret;
}

sge::systems::any_map const &
sge::systems::list::get() const
{
	return states_;
}
