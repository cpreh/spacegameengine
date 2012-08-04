#ifndef SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED
#define SGE_SCENIC_RENDER_CONTEXT_BASE_HPP_INCLUDED

#include <fcppt/noncopyable.hpp>
#include <sge/scenic/symbol.hpp>
#include <sge/class_symbol.hpp>

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
protected:
	base();
};
}
}
}

#endif
