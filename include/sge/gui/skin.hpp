#ifndef SGE_GUI_SKIN_HPP_INCLUDED
#define SGE_GUI_SKIN_HPP_INCLUDED

#include "../export.hpp"
#include "../shared_ptr.hpp"
#include "../path.hpp"

namespace sge
{
namespace gui
{
// forward declarations
class widget;

namespace events 
{
class invalid_area;
}

namespace widgets
{
class button;
}


class skin
{
	public:
	SGE_SYMBOL void draw(widget &,events::invalid_area const &);
	virtual void operator()(widgets::button &,events::invalid_area const &) = 0;
	virtual path const cursor_path() const = 0;
	virtual void default_handler(widget &,events::invalid_area const &);
	virtual ~skin() {}
};

typedef shared_ptr<skin> skin_ptr;
}
}

#endif
