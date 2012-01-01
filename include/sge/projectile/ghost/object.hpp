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


#ifndef SGE_PROJECTILE_GHOST_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_OBJECT_HPP_INCLUDED

#include <sge/projectile/symbol.hpp>
#include <sge/projectile/vector2.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/ghost/body_enter.hpp>
#include <sge/projectile/ghost/body_enter_fn.hpp>
#include <sge/projectile/ghost/body_exit.hpp>
#include <sge/projectile/ghost/body_exit_fn.hpp>
#include <sge/projectile/ghost/parameters_fwd.hpp>
#include <sge/projectile/ghost/detail/pair_callback_fwd.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>


class btCollisionShape;
class btPairCachingGhostObject;

namespace sge
{
namespace projectile
{
namespace ghost
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_PROJECTILE_SYMBOL explicit
	object(
		parameters const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::vector2 const
	position() const;

	SGE_PROJECTILE_SYMBOL void
	position(
		sge::projectile::vector2 const &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	body_enter(
		sge::projectile::ghost::body_enter const &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	body_exit(
		sge::projectile::ghost::body_exit const &);

	SGE_PROJECTILE_SYMBOL ~object();
private:
	friend class detail::pair_callback;
	friend class sge::projectile::world;

	fcppt::signal::object<body_enter_fn> body_enter_;
	fcppt::signal::object<body_exit_fn> body_exit_;
	fcppt::scoped_ptr<btCollisionShape> box_shape_;
	fcppt::scoped_ptr<btPairCachingGhostObject> ghost_object_;

	void
	enter_internal(
		body::object const &);

	void
	exit_internal(
		body::object const &);
};
}
}
}

#endif
