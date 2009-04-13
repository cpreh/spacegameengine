#ifndef SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED

#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/activation_state.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/point.hpp>
#include <sge/gui/rect.hpp>
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
	virtual void resize(
		widget &,
		dim const &);
	virtual void reposition(
		widget &,
		point const &);
	virtual void update();
	virtual void add(
		widget &);
	virtual void activation(
		widget &,
		activation_state::type);
	virtual void remove(
		widget &);
	virtual void dirty(
		widget &,
		rect const &);
	virtual void invalidate(
		widget &);
	virtual ~submanager();
};
}
}
}

#endif
