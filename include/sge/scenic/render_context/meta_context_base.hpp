#ifndef SGE_SCENIC_RENDER_CONTEXT_META_CONTEXT_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_META_CONTEXT_BASE_HPP_INCLUDED

#include <sge/renderer/device_fwd.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/renderer/context/object_fwd.hpp>
#include <sge/class_symbol.hpp>
#include <sge/scenic/render_context/base_unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>

namespace sge
{
namespace scenic
{
namespace render_context
{
class SGE_CLASS_SYMBOL meta_context_base
{
FCPPT_NONCOPYABLE(
	meta_context_base);
public:
	virtual
	sge::scenic::render_context::base_unique_ptr
	wrap_context(
		sge::renderer::context::object &) = 0;

	virtual ~meta_context_base() = 0;
protected:
	meta_context_base();
};
}
}
}

#endif
