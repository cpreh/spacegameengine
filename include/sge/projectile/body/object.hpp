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


#ifndef SGE_PROJECTILE_BODY_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_OBJECT_HPP_INCLUDED

#include <sge/projectile/body/detail/motion_state_fwd.hpp>
#include <sge/projectile/body/parameters_fwd.hpp>
#include <sge/projectile/body/position_change_fn.hpp>
#include <sge/projectile/body/position_change.hpp>
#include <sge/projectile/body/rotation_change.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/group/object_fwd.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <sge/projectile/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/math/vector/basic_decl.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object.hpp>
#include <fcppt/scoped_ptr.hpp>

class btRigidBody;
class btTransform;

namespace sge
{
namespace projectile
{
namespace body
{
class object
{
FCPPT_NONCOPYABLE(
	object);
public:
	SGE_PROJECTILE_SYMBOL explicit
	object(
		parameters const &);
	
	SGE_PROJECTILE_SYMBOL vector2 const 
	position() const;
	
	SGE_PROJECTILE_SYMBOL void 
	position(
		vector2 const &);

	SGE_PROJECTILE_SYMBOL vector2 const 
	linear_velocity() const;
	
	SGE_PROJECTILE_SYMBOL void 
	linear_velocity(
		vector2 const &);

	SGE_PROJECTILE_SYMBOL scalar
	angular_velocity() const;

	SGE_PROJECTILE_SYMBOL void
	angular_velocity(
		scalar);

	SGE_PROJECTILE_SYMBOL sge::projectile::shape::shared_base_ptr const
	shape() const;
		
	SGE_PROJECTILE_SYMBOL scalar
	rotation() const;
	
	SGE_PROJECTILE_SYMBOL void 
	rotation(
		scalar);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	position_change(
		sge::projectile::body::position_change const &);

	SGE_PROJECTILE_SYMBOL fcppt::signal::auto_connection
	rotation_change(
		sge::projectile::body::rotation_change const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::body::user_data const &
	user_data() const;
		
	SGE_PROJECTILE_SYMBOL ~object();
private:
	friend class sge::projectile::body::detail::motion_state;
	friend class sge::projectile::world;

	fcppt::scoped_ptr<btTransform> transformation_;
	fcppt::scoped_ptr<detail::motion_state> motion_state_;
	fcppt::signal::object<position_change_fn> position_change_;
	fcppt::signal::object<rotation_change_fn> rotation_change_;
	shape::shared_base_ptr shape_;
	fcppt::scoped_ptr<btRigidBody> body_;
	sge::projectile::body::user_data user_data_;

	// @override
	void	
	getWorldTransform(
		btTransform &) const;

	// @override
	void	
	setWorldTransform(
		btTransform const &);
};
}
}
}

#endif
