//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_IMPL_PARAMETER_CONVERT_ELEMENT_TYPE_HPP_INCLUDED
#define SGE_CG_IMPL_PARAMETER_CONVERT_ELEMENT_TYPE_HPP_INCLUDED

#include <sge/cg/parameter/element_type_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::impl::parameter
{

CGtype convert_element_type(sge::cg::parameter::element_type);

}

#endif
