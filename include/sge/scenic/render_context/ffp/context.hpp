#ifndef SGE_SCENIC_RENDER_CONTEXT_FFP_CONTEXT_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_FFP_CONTEXT_HPP_INCLUDED

#include <sge/scenic/render_context/base.hpp>
#include <fcppt/noncopyable.hpp>
#include <sge/scenic/symbol.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
namespace ffp
{
class context
{
FCPPT_NONCOPYABLE(
	context);
public:
	SGE_SCENIC_SYMBOL
	context(
		sge::renderer::context::object &);
private:
		
};
}
}
}
}

#endif
