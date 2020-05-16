//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_OPTIONAL_NAMED_FWD_HPP_INCLUDED
#define SGE_CG_PARAMETER_OPTIONAL_NAMED_FWD_HPP_INCLUDED

#include <sge/cg/parameter/named_fwd.hpp>
#include <fcppt/optional/object_fwd.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{

using
optional_named
=
fcppt::optional::object<
	sge::cg::parameter::named
>;

}
}
}

#endif
