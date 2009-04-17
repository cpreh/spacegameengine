#ifndef SGE_GUI_WIDGETS_PARAMETERS_HPP_INCLUDED
#define SGE_GUI_WIDGETS_PARAMETERS_HPP_INCLUDED

#include <sge/gui/export.hpp>
#include <sge/gui/point.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/gui/dim.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <sge/gui/size_policy.hpp>
#include <sge/gui/layouts/fwd.hpp>
#include <sge/gui/keyboard_focus.hpp>
#include <sge/gui/activation_state.hpp>
#include <boost/optional.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
class parameters
{
	public:
	SGE_GUI_SYMBOL parameters();
	SGE_GUI_SYMBOL parameters &pos(point const &);
	SGE_GUI_SYMBOL parameters &size(dim const &);
	SGE_GUI_SYMBOL parameters &size_policy(sge::gui::size_policy const &);
	SGE_GUI_SYMBOL parameters &keyboard_focus(keyboard_focus::type const &);
	SGE_GUI_SYMBOL parameters &layout(layouts::auto_ptr);
	SGE_GUI_SYMBOL parameters &activation(activation_state::type);

	SGE_GUI_SYMBOL point const &pos() const;
	SGE_GUI_SYMBOL boost::optional<dim> const &size() const;
	SGE_GUI_SYMBOL sge::gui::size_policy const &size_policy() const;
	SGE_GUI_SYMBOL keyboard_focus::type const &keyboard_focus() const;
	SGE_GUI_SYMBOL layouts::auto_ptr layout() const;
	SGE_GUI_SYMBOL activation_state::type activation() const;
	private:
	point pos_;
	boost::optional<dim> size_;
	sge::gui::size_policy size_policy_;
	keyboard_focus::type keyboard_focus_;
	layouts::auto_ptr layout_;
	activation_state::type activation_;
};
}
}
}

#endif
