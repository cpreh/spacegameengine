#ifndef SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED
#define SGE_GUI_DETAIL_SUBMANAGER_HPP_INCLUDED

#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/invalidation.hpp>
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
	virtual void update();
	virtual void add(
		widgets::base &);
	virtual void activation(
		widgets::base &,
		activation_state::type);
	virtual void remove(
		widgets::base &);
	virtual void dirty(
		widgets::base &,
		rect const &);
	virtual void resize(
		widgets::base &,
		dim const &);
	virtual void reposition(
		widgets::base &,
		point const &);
	virtual void invalidate(
		widgets::base &,
		invalidation::type const &);
	virtual ~submanager();
};
}
}
}

#endif
