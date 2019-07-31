//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_BODY_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/parameters_fwd.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace body
{

class parameters
{
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	parameters(
		sge::projectile::log const &,
		sge::projectile::body::position const &,
		sge::projectile::body::linear_velocity const &,
		sge::projectile::body::angular_velocity const &,
		sge::projectile::shape::shared_base_ptr const &,
		sge::projectile::body::rotation const &,
		sge::projectile::body::solidity::variant const &,
		sge::projectile::body::user_data const &
	);

	fcppt::log::object &
	log() const;

	sge::projectile::body::position const &
	position() const;

	sge::projectile::body::linear_velocity const &
	linear_velocity() const;

	sge::projectile::body::angular_velocity const &
	angular_velocity() const;

	sge::projectile::shape::shared_base_ptr const &
	shape() const;

	sge::projectile::body::rotation const &
	rotation() const;

	sge::projectile::body::solidity::variant const &
	solidity() const;

	sge::projectile::body::user_data const &
	user_data() const;
private:
	fcppt::reference<
		fcppt::log::object
	> log_;

	sge::projectile::body::position position_;

	sge::projectile::body::linear_velocity linear_velocity_;

	sge::projectile::body::angular_velocity angular_velocity_;

	sge::projectile::shape::shared_base_ptr shape_;

	sge::projectile::body::rotation rotation_;

	sge::projectile::body::solidity::variant solidity_;

	sge::projectile::body::user_data user_data_;
};

}
}
}

#endif
