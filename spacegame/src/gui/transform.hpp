#ifndef SGE_GUI_TRANSFORM_HPP_INCLUDED
#define SGE_GUI_TRANSFORM_HPP_INCLUDED

#include "../core/renderer/renderer_types.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui
{

pos3 gui_to_space(point p);
pos3 gui_to_space(unit x, unit y);

}
}

#endif
