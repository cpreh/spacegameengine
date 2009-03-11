#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

#include <sge/gui/types.hpp>
#include <sge/gui/canvas_fwd.hpp>
#include <sge/filesystem/path.hpp>
#include <sge/export.hpp>
#include <sge/shared_ptr.hpp>
#include <sge/gui/events/fwd.hpp>
#include <sge/gui/widget_fwd.hpp>
#include <sge/gui/widgets/fwd.hpp>

namespace sge
{
namespace gui
{
class skin
{
	public:
	SGE_SYMBOL void draw(widget &,events::invalid_area const &);
	SGE_SYMBOL dim const size_hint(widget const &) const;

	virtual void fallback(widget const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::buttons::text const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::buttons::image const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::edit const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::label const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::graphics const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::backdrop const &,events::invalid_area const &) = 0;
	virtual dim const size_hint(widgets::buttons::text const &) const = 0;
	virtual dim const size_hint(widgets::buttons::image const &) const = 0;
	virtual dim const size_hint(widgets::edit const &) const = 0;
	virtual dim const size_hint(widgets::label const &) const = 0;
	virtual dim const size_hint(widgets::graphics const &) const = 0;
	virtual dim const size_hint(widgets::backdrop const &) const = 0;
	virtual filesystem::path const cursor_path() const = 0;
	virtual void default_handler(widget &,events::invalid_area const &);
	virtual dim const default_hint_handler(widget const &) const;
	SGE_SYMBOL virtual ~skin();

	protected:
	// NOTE: this can be a const widget since the buffer is mutable
	void resize_buffer(
		widget const &);
	void blit_invalid(
		widget const &,
		canvas::object &,
		events::invalid_area const &);
};

typedef shared_ptr<skin> skin_ptr;
typedef shared_ptr<skin const> const_skin_ptr;
}
}

#endif
