#ifndef SGE_RENDERER_CONTEXT_SCOPED_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/context/scoped_fwd.hpp>
#include <fcppt/unique_ptr.hpp>

namespace sge
{
namespace renderer
{
namespace context
{
typedef
fcppt::unique_ptr<sge::renderer::context::scoped>
scoped_unique_ptr;
}
}
}

#endif
