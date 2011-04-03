#ifndef SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/symbol.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/size.hpp>
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
		sge::projectile::ghost::position const &,
		sge::projectile::ghost::size const &);

	SGE_PROJECTILE_SYMBOL sge::projectile::ghost::position const &
	position() const;

	SGE_PROJECTILE_SYMBOL sge::projectile::ghost::size const &
	size() const;
private:
	sge::projectile::ghost::position position_;
	sge::projectile::ghost::size size_;
};
}
}
}

#endif
