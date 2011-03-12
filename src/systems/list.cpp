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


#include "any_compare.hpp"
#include <sge/systems/list.hpp>
#include <sge/log/global.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <ostream>

namespace
{

sge::systems::any_set const
init_states()
{
	return
		sge::systems::any_set(
			std::tr1::bind(
				sge::systems::any_compare,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			)
		);
}

}

sge::systems::list::list()
:
	states_(
		init_states()
	)
{}

sge::systems::list::list(
	systems::any const &_any
)
:
	states_(
		init_states()
	)
{
	states_.insert(
		_any
	);
}

sge::systems::list const
sge::systems::list::operator()(
	systems::any const &_any
) const
{
	list ret(*this);

	if(
		!ret.states_.insert(
			_any
		).second
	)
	{
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("Duplicate system state given!")
		);
	}

	return ret;
}

sge::systems::list const
sge::systems::list::append(
	systems::list const &_other
) const
{
	systems::list ret(*this);

	// TODO: this could be optimized
	BOOST_FOREACH(
		any_set::const_reference ref,
		_other.get()
	)
		ret = ret(ref);
	
	return ret;
}

sge::systems::any_set const &
sge::systems::list::get() const
{
	return states_;
}
