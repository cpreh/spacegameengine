#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

#include "types.hpp"
#include "../export.hpp"
#include "../shared_ptr.hpp"
#include "../path.hpp"
#include "events/fwd.hpp"
#include "widget_fwd.hpp"
#include "widgets/fwd.hpp"

namespace sge
{
namespace gui
{
class skin
{
	public:
	SGE_SYMBOL void draw(widget &,events::invalid_area const &);
	SGE_SYMBOL dim const size_hint(widget const &) const;

	virtual void draw(widgets::button const &,events::invalid_area const &) = 0;
	virtual void draw(widgets::edit const &,events::invalid_area const &) = 0;
	virtual dim const size_hint(widgets::button const &) const = 0;
	virtual dim const size_hint(widgets::edit const &) const = 0;
	virtual path const cursor_path() const = 0;
	virtual void default_handler(widget &,events::invalid_area const &);
	virtual dim const default_hint_handler(widget const &) const;
	virtual ~skin() {}
};

typedef shared_ptr<skin> skin_ptr;
typedef shared_ptr<skin const> const_skin_ptr;
}
}

#endif
