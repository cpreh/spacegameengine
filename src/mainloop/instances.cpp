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


#include <sge/mainloop/instances.hpp>
#include <sge/mainloop/dispatchable.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/global.hpp>
#include <fcppt/text.hpp>
#include <boost/foreach.hpp>
#include <ostream>
#include <set>

namespace
{

typedef std::set<
	sge::mainloop::dispatchable *
> instance_set;

instance_set instances;

}

void sge::mainloop::add_instance(
	dispatchable *const i)
{
	if(!instances.insert(i).second)
		SGE_LOG_WARNING(
			log::global(),
			log::_
				<< FCPPT_TEXT("mainloop instance inserted twice!"));
}

void sge::mainloop::remove_instance(
	dispatchable *const i)
{
	if(!instances.erase(i))
		SGE_LOG_WARNING(
			log::global(),
			log::_
				<< FCPPT_TEXT("mainloop instance not found!"));
}

void sge::mainloop::dispatch_instances()
{
	BOOST_FOREACH(instance_set::const_reference i, instances)
		i->dispatch();
}
