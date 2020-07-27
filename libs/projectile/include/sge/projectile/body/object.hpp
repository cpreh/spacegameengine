//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_OBJECT_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_OBJECT_HPP_INCLUDED

#include <sge/projectile/scalar.hpp>
#include <sge/projectile/vector2_fwd.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/parameters_fwd.hpp>
#include <sge/projectile/body/position_change.hpp>
#include <sge/projectile/body/position_change_fn.hpp>
#include <sge/projectile/body/rotation_change.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/detail/motion_state_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/signal/auto_connection_fwd.hpp>
#include <fcppt/signal/object_decl.hpp>


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
	FCPPT_NONMOVABLE(
		object
	);
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	explicit
	object(
		sge::projectile::body::parameters const &
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::vector2
	position() const;

	SGE_PROJECTILE_DETAIL_SYMBOL
	void
	position(
		sge::projectile::vector2 const &
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::vector2
	linear_velocity() const;

	SGE_PROJECTILE_DETAIL_SYMBOL
	void
	linear_velocity(
		sge::projectile::vector2 const &
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::scalar
	angular_velocity() const;

	SGE_PROJECTILE_DETAIL_SYMBOL
	void
	angular_velocity(
		sge::projectile::scalar
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::shape::shared_base_ptr
	shape() const;

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::scalar
	rotation() const;

	SGE_PROJECTILE_DETAIL_SYMBOL
	void
	rotation(
		sge::projectile::scalar
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	position_change(
		sge::projectile::body::position_change &&
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	fcppt::signal::auto_connection
	rotation_change(
		sge::projectile::body::rotation_change &&
	);

	[[nodiscard]]
	SGE_PROJECTILE_DETAIL_SYMBOL
	sge::projectile::body::user_data const &
	user_data() const;

	SGE_PROJECTILE_DETAIL_SYMBOL
	~object();
private:
	friend class sge::projectile::body::detail::motion_state;
	friend class sge::projectile::world;

	fcppt::log::object &log_;
	fcppt::unique_ptr<btTransform> const transformation_;
	fcppt::unique_ptr<sge::projectile::body::detail::motion_state> const motion_state_;
	fcppt::signal::object<sge::projectile::body::position_change_fn> position_change_;
	fcppt::signal::object<sge::projectile::body::rotation_change_fn> rotation_change_;
	sge::projectile::shape::shared_base_ptr shape_;
	fcppt::unique_ptr<btRigidBody>const body_;
	sge::projectile::body::user_data user_data_;

	// @override
	void
	getWorldTransform(
		btTransform & // NOLINT(google-runtime-references)
	) const; // NOLINT(google-runtime-references)

	// @override
	void
	setWorldTransform(
		btTransform const &
	);
};

}
}
}

#endif
