#ifndef SGE_GUI_WIDGETS_BUTTONS_TEXT_HPP_INCLUDED
#define SGE_GUI_WIDGETS_BUTTONS_TEXT_HPP_INCLUDED

#include <sge/gui/widgets/buttons/base.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/font_info.hpp>
#include <boost/function.hpp>

namespace sge
{
namespace gui
{
namespace widgets
{
namespace buttons
{
class SGE_CLASS_SYMBOL text : public base
{
	public:
	SGE_GUI_SYMBOL text(
		parent_data const &,
		parameters,
		string const &);

	string const caption() const;
	private:
	string caption_;
};
}
}
}
}

#endif
