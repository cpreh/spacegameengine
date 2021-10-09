//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_PROJECTILE_BODY_CONST_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_CONST_OPTIONAL_OBJECT_REF_FWD_HPP_INCLUDED

#include <sge/projectile/body/object_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>

namespace sge
{
namespace projectile
{
namespace body
{

typedef fcppt::optional::object<sge::projectile::body::object const &> const_optional_object_ref;

}
}
}

#endif
