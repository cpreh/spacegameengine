#ifndef SGE_GUI_SKINS_BASE_HPP_INCLUDED
#define SGE_GUI_SKINS_BASE_HPP_INCLUDED

#include <sge/gui/events/fwd.hpp>
#include <sge/gui/widgets/fwd.hpp>
#include <sge/gui/dim.hpp>
#include <sge/gui/canvas/fwd.hpp>
#include <sge/gui/export.hpp>
#include <sge/gui/font_info.hpp>
#include <sge/auto_ptr.hpp>
#include <sge/filesystem/path.hpp>

#define SGE_GUI_SKIN_DRAW_RETURN(name)\
	void

#define SGE_GUI_SKIN_SIZE_RETURN(name)\
	sge::gui::dim const

#define SGE_GUI_SKIN_DRAW_PARAMS(name)\
	name const &,\
	sge::gui::events::invalid_area const &

#define SGE_GUI_SKIN_DRAW_PARAMS_NAMED(name)\
	name const &w,\
	sge::gui::events::invalid_area const &e

#define SGE_GUI_SKIN_SIZE_PARAMS(name)\
	name const &

#define SGE_GUI_SKIN_SIZE_PARAMS_NAMED(name)\
	name const &w

#define SGE_GUI_SKIN_WIDGET_PURE(name)\
	virtual SGE_GUI_SKIN_DRAW_RETURN(name) draw(\
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::name)) = 0;\
	virtual SGE_GUI_SKIN_SIZE_RETURN(name) size_hint(\
		SGE_GUI_SKIN_SIZE_PARAMS(widgets::name)) const = 0;

#define SGE_GUI_SKIN_WIDGET(name)\
	virtual SGE_GUI_SKIN_DRAW_RETURN(name) draw(\
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::name));\
	virtual SGE_GUI_SKIN_SIZE_RETURN(name) size_hint(\
		SGE_GUI_SKIN_SIZE_PARAMS(widgets::name)) const;

#define SGE_GUI_SKIN_WIDGETS_PURE\
	SGE_GUI_WIDGETS_FWD_APPLY(\
		SGE_GUI_SKIN_WIDGET_PURE,\
		SGE_GUI_SKIN_WIDGET_PURE,\
		SGE_GUI_SKIN_WIDGET_PURE)

#define SGE_GUI_SKIN_WIDGETS\
	SGE_GUI_WIDGETS_FWD_APPLY(\
		SGE_GUI_SKIN_WIDGET,\
		SGE_GUI_SKIN_WIDGET,\
		SGE_GUI_SKIN_WIDGET)

namespace sge
{
namespace gui
{
namespace skins
{
class base
{
	public:
	SGE_GUI_SYMBOL SGE_GUI_SKIN_WIDGET(base)

	virtual SGE_GUI_SKIN_DRAW_RETURN(widgets::base) fallback(
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::base)) = 0;
	SGE_GUI_SYMBOL virtual SGE_GUI_SKIN_DRAW_RETURN(widgets::base) default_handler(
		SGE_GUI_SKIN_DRAW_PARAMS(widgets::base));
	SGE_GUI_SYMBOL virtual SGE_GUI_SKIN_SIZE_RETURN(widgets::base) default_hint_handler(
		SGE_GUI_SKIN_SIZE_PARAMS(widgets::base)) const;

	SGE_GUI_SKIN_WIDGETS_PURE
	
	virtual font_info const standard_font() const = 0;

	SGE_GUI_SYMBOL virtual ~base();
	protected:
	// NOTE: this can be a const widgets::base since the buffer is mutable
	void resize_buffer(
		widgets::base const &);
	void blit_invalid(
		widgets::base const &,
		canvas::object &,
		events::invalid_area const &,
		bool transparency = true);
};

typedef auto_ptr<base> ptr;
typedef auto_ptr<base const> const_ptr;
}
}
}

#endif
