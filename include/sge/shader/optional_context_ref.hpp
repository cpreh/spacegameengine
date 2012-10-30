#ifndef SGE_SHADER_OPTIONAL_CONTEXT_REF_HPP_INCLUDED
#define SGE_SHADER_OPTIONAL_CONTEXT_REF_HPP_INCLUDED

#include <fcppt/optional_fwd.hpp>
#include <sge/shader/context_fwd.hpp>

namespace sge
{
namespace shader
{
typedef
fcppt::optional<sge::shader::context &>
optional_context_ref;
}
}

#endif
