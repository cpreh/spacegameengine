#ifndef SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED

#include "../widget_fwd.hpp"
#include "../activation_state.hpp"
#include "../types.hpp"
#include <sge/noncopyable.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class submanager
{
	SGE_NONCOPYABLE(submanager)
	protected:
	submanager();
	public:
	virtual void resize(widget &,dim const &);
	virtual void reposition(widget &,point const &);
	virtual void draw();
	virtual void add(widget &);
	virtual void activation(widget &,activation_state::type);
	virtual void remove(widget &);
	virtual void invalidate(rect const &);
	virtual ~submanager();
};
}
}
}

#endif
