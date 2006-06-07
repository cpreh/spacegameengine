#ifndef SGE_GUI_FRAME_HPP_INCLUDED
#define SGE_GUI_FRAME_HPP_INCLUDED

#include "./types.hpp"
#include "./rectangle.hpp"
#include "./element.hpp"

namespace sge
{
namespace gui
{
	class manager;

	class frame : public rectangle {
	public:
		SGEGUIDLLAPI frame(manager& man, element* parent, point pos, dim sz, const std::string& my_texture, bool visible = true, bool enabled = true);
	};
	typedef shared_ptr<frame> frame_ptr;
}
}

#endif
