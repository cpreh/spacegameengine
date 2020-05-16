//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PARAMETER_MATRIX_DETAIL_CHECK_SIZE_HPP_INCLUDED
#define SGE_CG_PARAMETER_MATRIX_DETAIL_CHECK_SIZE_HPP_INCLUDED

#include <sge/cg/detail/symbol.hpp>
#include <sge/cg/parameter/object_fwd.hpp>
#include <sge/cg/parameter/matrix/detail/size_fwd.hpp>


namespace sge
{
namespace cg
{
namespace parameter
{
namespace matrix
{
namespace detail
{

SGE_CG_DETAIL_SYMBOL
void
check_size(
	sge::cg::parameter::object const &,
	sge::cg::parameter::matrix::detail::size const &
);

}
}
}
}
}

#endif
