#ifndef SGE_GUI_LAYOUTS_BASE_HPP_INCLUDED
#define SGE_GUI_LAYOUTS_BASE_HPP_INCLUDED

#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/layouts/fwd.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/invalidation.hpp>
#include <sge/gui/export.hpp>

namespace sge
{
namespace gui
{
namespace layouts
{
class SGE_CLASS_SYMBOL base
{
public:
	SGE_GUI_SYMBOL base();

	virtual void compile(invalidation::type const &) = 0;
	virtual dim const size_hint() const = 0;
	SGE_GUI_SYMBOL virtual void invalidate(
		widgets::base &,
		invalidation::type const &);

	SGE_GUI_SYMBOL widgets::base &connected_widget();
	SGE_GUI_SYMBOL widgets::base const &connected_widget() const;

	SGE_GUI_SYMBOL virtual ~base();
protected:
	void set_widget_size(
		widgets::base &,
		dim const &);
	void set_widget_pos(
		widgets::base &,
		point const &);
	void compile_widget(
		widgets::base &,
		invalidation::type const &);

private:
	widgets::base *w;

	friend class widgets::base;
	void connected_widget(widgets::base &);
};

}
}
}

#endif
