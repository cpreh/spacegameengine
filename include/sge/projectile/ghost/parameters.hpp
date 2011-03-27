#ifndef SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/symbol.hpp>
#include <sge/projectile/ghost/user_data.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <sge/projectile/group/sequence.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/nonassignable.hpp>

namespace sge
{
namespace projectile
{
namespace ghost
{
class parameters
{
FCPPT_NONASSIGNABLE(
	parameters);
public:
	SGE_PROJECTILE_SYMBOL explicit
	parameters(
		sge::projectile::world &,
		sge::projectile::ghost::position const &,
		sge::projectile::ghost::size const &,
		sge::projectile::group::sequence const &,
		sge::projectile::ghost::user_data const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::world &
	world() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::ghost::position const &
	position() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::ghost::size const &
	size() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::group::sequence const &
	groups() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::ghost::user_data const &
	user_data() const;
private:
	sge::projectile::world &world_;
	sge::projectile::ghost::position position_;
	sge::projectile::ghost::size size_;
	sge::projectile::group::sequence groups_;
	sge::projectile::ghost::user_data user_data_;
};
}
}
}

#endif
