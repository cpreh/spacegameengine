#ifndef SGE_PROJECTILE_BODY_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/body/user_data.hpp>
#include <sge/projectile/body/solidity/variant.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/math/vector/basic_impl.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_PROJECTILE_SYMBOL explicit
	parameters(
		sge::projectile::world &,
		sge::projectile::body::position const &,
		sge::projectile::body::linear_velocity const &,
		sge::projectile::shape::shared_base_ptr const &,
		sge::projectile::body::rotation const &,
		sge::projectile::body::solidity::variant const &,
		sge::projectile::group::sequence const &,
		sge::projectile::body::user_data const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::world &
	world() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::position const &
	position() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::linear_velocity const &
	linear_velocity() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::shape::shared_base_ptr const &
	shape() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::rotation const &
	rotation() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::solidity::variant const &
	solidity() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::group::sequence const &
	groups() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::body::user_data const &
	user_data() const;
private:
	sge::projectile::world &world_;
	sge::projectile::body::position position_;
	sge::projectile::body::linear_velocity linear_velocity_;
	sge::projectile::shape::shared_base_ptr shape_;
	sge::projectile::body::rotation rotation_;
	sge::projectile::body::solidity::variant solidity_;
	sge::projectile::group::sequence groups_;
	sge::projectile::body::user_data user_data_;
};
}
}
}

#endif
