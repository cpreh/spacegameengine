//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef SGE_CG_IMPL_PROGRAM_CONVERT_SOURCE_TYPE_HPP_INCLUDED
#define SGE_CG_IMPL_PROGRAM_CONVERT_SOURCE_TYPE_HPP_INCLUDED

#include <sge/cg/program/source_type_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <Cg/cg.h>
#include <fcppt/config/external_end.hpp>

namespace sge::cg::impl::program
{

CGenum convert_source_type(sge::cg::program::source_type);

}

#endif
