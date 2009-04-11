#ifndef SGE_GUI_LAYOUT_HPP_INCLUDED
#define SGE_GUI_LAYOUT_HPP_INCLUDED

#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/layout_fwd.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
class SGE_CLASS_SYMBOL layout
{
public:
	SGE_GUI_SYMBOL layout();

	virtual void update() = 0;
	virtual void pos(point const &) = 0;
	virtual void size(dim const &) = 0;
	virtual dim const size_hint() const = 0;

	SGE_GUI_SYMBOL widget &connected_widget();
	SGE_GUI_SYMBOL widget const &connected_widget() const;

	SGE_GUI_SYMBOL virtual ~layout();
protected:
	void set_widget_size(widget &,dim const &);
	void set_widget_pos(widget &,point const &);
	void compile_widget(widget &);

private:
	widget *w;

	friend class widget;
	void connected_widget(widget &);
};

}
}

#endif
