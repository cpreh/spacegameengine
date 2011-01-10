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


#ifndef SGE_BULLET_OVERLAP_FILTER_HPP_INCLUDED
#define SGE_BULLET_OVERLAP_FILTER_HPP_INCLUDED

#include <sge/collision/test_callback_fn.hpp>
#include <sge/collision/test_callback.hpp>
#include <sge/collision/test_callback_combiner.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <BulletCollision/BroadphaseCollision/btOverlappingPairCache.h>

namespace sge
{
namespace bullet
{
class overlap_filter
:
	public btOverlapFilterCallback
{
public:
	overlap_filter();

	~overlap_filter();

	bool 
	needBroadphaseCollision(
		btBroadphaseProxy*,
		btBroadphaseProxy*) const;
	
	fcppt::signal::auto_connection
	register_callback(
		collision::test_callback const &);
	
	void
	combiner(
		collision::test_callback_combiner const &);
private:
	fcppt::signal::object
	<
		collision::test_callback_fn
	> test_callback_;
};
}
}

#endif
