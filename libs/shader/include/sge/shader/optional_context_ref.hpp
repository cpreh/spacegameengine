//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_OPTIONAL_CONTEXT_REF_HPP_INCLUDED
#define SGE_SHADER_OPTIONAL_CONTEXT_REF_HPP_INCLUDED

#include <sge/shader/context_fwd.hpp>
#include <fcppt/optional/reference.hpp>


namespace sge
{
namespace shader
{
typedef
fcppt::optional::reference<sge::shader::context>
optional_context_ref;
}
}

#endif
