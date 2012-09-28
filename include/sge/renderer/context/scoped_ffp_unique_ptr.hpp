#ifndef SGE_RENDERER_CONTEXT_SCOPED_FFP_UNIQUE_PTR_HPP_INCLUDED
#define SGE_RENDERER_CONTEXT_SCOPED_FFP_UNIQUE_PTR_HPP_INCLUDED

#include <sge/renderer/context/scoped_ffp_fwd.hpp>
#include <fcppt/unique_ptr_impl.hpp>

namespace sge
{
namespace renderer
{
namespace context
{
typedef
fcppt::unique_ptr<
	sge::renderer::context::scoped_ffp
>
scoped_ffp_unique_ptr;
}
}
}

#endif
