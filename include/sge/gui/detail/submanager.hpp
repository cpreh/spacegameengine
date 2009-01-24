#ifndef SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED

#include "../widget_fwd.hpp"
#include "../types.hpp"
#include <boost/noncopyable.hpp>

namespace sge
{
namespace gui
{
namespace detail
{
class submanager : public boost::noncopyable
{
	public:
	virtual void resize(widget &,dim const &);
	virtual void reposition(widget &,point const &);
	virtual void draw();
	virtual void add(widget &);
	//virtual void activation(widget &,activation_state::type);
	virtual void remove(widget &);
	virtual void invalidate(rect const &);
	virtual ~submanager();
};
}
}
}

#endif
