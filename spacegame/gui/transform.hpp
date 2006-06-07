#ifndef SGE_GUI_TRANSFORM_HPP_INCLUDED
#define SGE_GUI_TRANSFORM_HPP_INCLUDED

#include "../core/main/types.hpp"
#include "../core/renderer/renderer_types.hpp"
#include "../core/input/key_type.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui
{
	SGEGUIDLLAPI pos3 gui_to_space(point p);
	SGEGUIDLLAPI pos3 gui_to_space(unit x, unit y);
}
}

#endif
