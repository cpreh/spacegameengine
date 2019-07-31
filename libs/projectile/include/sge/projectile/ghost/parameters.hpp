//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED
#define SGE_PROJECTILE_GHOST_PARAMETERS_HPP_INCLUDED

#include <sge/projectile/log_fwd.hpp>
#include <sge/projectile/detail/symbol.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge
{
namespace projectile
{
namespace ghost
{

class parameters
{
public:
	SGE_PROJECTILE_DETAIL_SYMBOL
	parameters(
		sge::projectile::log const &,
		sge::projectile::ghost::position const &,
		sge::projectile::ghost::size const &
	);

	fcppt::log::object &
	log() const;

	sge::projectile::ghost::position const &
	position() const;

	sge::projectile::ghost::size const &
	size() const;
private:
	fcppt::reference<
		fcppt::log::object
	> log_;

	sge::projectile::ghost::position position_;

	sge::projectile::ghost::size size_;
};

}
}
}

#endif
