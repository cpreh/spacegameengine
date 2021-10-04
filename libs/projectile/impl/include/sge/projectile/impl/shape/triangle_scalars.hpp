//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_IMPL_SHAPE_TRIANGLE_SCALARS_HPP_INCLUDED
#define SGE_PROJECTILE_IMPL_SHAPE_TRIANGLE_SCALARS_HPP_INCLUDED

#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/shape/detail/scalar_container.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sge::projectile::impl::shape
{

sge::projectile::shape::detail::scalar_container
triangle_scalars(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	sge::projectile::shape::triangle_sequence const &
);

}

#endif
