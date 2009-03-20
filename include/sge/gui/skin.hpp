#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

#include <sge/gui/dim.hpp>
#include <sge/gui/canvas_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/export.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/widgets/fwd.hpp>

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
class skin
{
	public:
	SGE_SYMBOL SGE_GUI_SKIN_DRAW_RETURN(widget) draw(
		SGE_GUI_SKIN_DRAW_PARAMS(widget));
	SGE_SYMBOL SGE_GUI_SKIN_SIZE_RETURN(widget) size_hint(
		SGE_GUI_SKIN_SIZE_PARAMS(widget)) const;

	virtual SGE_GUI_SKIN_DRAW_RETURN(widget) fallback(
		SGE_GUI_SKIN_DRAW_PARAMS(widget)) = 0;
	virtual SGE_GUI_SKIN_DRAW_RETURN(widget) default_handler(
		SGE_GUI_SKIN_DRAW_PARAMS(widget));
	virtual SGE_GUI_SKIN_SIZE_RETURN(widget) default_hint_handler(
		SGE_GUI_SKIN_SIZE_PARAMS(widget)) const;

	virtual filesystem::path const cursor_path() const = 0;
	SGE_SYMBOL virtual ~skin();

	SGE_GUI_SKIN_WIDGETS_PURE

	protected:
	// NOTE: this can be a const widget since the buffer is mutable
	void resize_buffer(
		widget const &);
	void blit_invalid(
		widget const &,
		canvas::object &,
		events::invalid_area const &,
		bool transparency = true);
};

typedef shared_ptr<skin> skin_ptr;
typedef shared_ptr<skin const> const_skin_ptr;
}
}

#endif
