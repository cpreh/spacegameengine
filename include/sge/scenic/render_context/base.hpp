#ifndef SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED

#include <sge/class_symbol.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace scenic
{
namespace render_context
{
class SGE_CLASS_SYMBOL base
{
FCPPT_NONCOPYABLE(
	base);
public:
	virtual ~base() = 0;

	virtual
	sge::renderer::context::object &
	core_context() = 0;
protected:
	base();
};
}
}
}

#endif
