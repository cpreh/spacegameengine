#ifndef SGE_GUI_LAYOUT_HPP_INCLUDED
#define SGE_GUI_LAYOUT_HPP_INCLUDED

#include "types.hpp"
#include "../export.hpp"
#include <boost/scoped_ptr.hpp>
#include <memory>

namespace sge
{
namespace gui
{
class widget;
namespace widgets
{
class container;
}

class SGE_CLASS_SYMBOL layout
{
	public:
	SGE_SYMBOL layout(widgets::container &);

	virtual void update() = 0;
	virtual dim const size_hint() const = 0;

	widgets::container &connected_widget() { return w; }
	widgets::container const &connected_widget() const { return w; }

	virtual ~layout() {}
	protected:
	void set_widget_size(widget &,dim const &);
	void set_widget_pos(widget &,point const &);
	void widget_compile(widget &);

	private:
	widgets::container &w;
};

typedef boost::scoped_ptr<layout> layout_auto_ptr;
typedef layout* layout_ptr;
typedef layout const * const_layout_ptr;
}
}

#endif
