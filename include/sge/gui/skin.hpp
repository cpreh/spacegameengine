#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

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
	virtual void operator()(widgets::button const &,events::invalid_area const &) = 0;
	virtual void operator()(widgets::edit const &,events::invalid_area const &) = 0;
	virtual path const cursor_path() const = 0;
	virtual void default_handler(widget &,events::invalid_area const &);
	virtual ~skin() {}
};

typedef shared_ptr<skin> skin_ptr;
}
}

#endif
