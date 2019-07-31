//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_VECTOR_DETAIL_SET_INT_HPP_INCLUDED
#define SGE_CG_PARAMETER_VECTOR_DETAIL_SET_INT_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <fcppt/math/size_type.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace vector
{
namespace detail
{

SGE_CG_DETAIL_SYMBOL
void
set_int(
	sge::cg::parameter::object const &,
	int const *,
	fcppt::math::size_type
);

}
}
}
}
}

#endif
