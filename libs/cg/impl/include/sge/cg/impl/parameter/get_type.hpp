//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_IMPL_PARAMETER_GET_TYPE_HPP_INCLUDED
#define SGE_CG_IMPL_PARAMETER_GET_TYPE_HPP_INCLUDED

#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace impl
{
namespace parameter
{

CGtype
get_type(
	sge::cg::parameter::object const &
);

}
}
}
}

#endif
