//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PROJECTILE_SHAPE_SHARED_BASE_PTR_HPP_INCLUDED
#define SGE_PROJECTILE_SHAPE_SHARED_BASE_PTR_HPP_INCLUDED

#include <sge/projectile/shape/base_fwd.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge::projectile::shape
{

using
shared_base_ptr
=
fcppt::shared_ptr<
	sge::projectile::shape::base
>;

}

#endif
