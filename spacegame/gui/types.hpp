#ifndef SGE_GUI_TYPES_HPP_INCLUDED
#define SGE_GUI_TYPES_HPP_INCLUDED

#include "../core/math/vector2.hpp"
#include "../core/math/rect.hpp"
#include "../core/math/dim.hpp"
#include "../core/main/types.hpp"
#include "../core/main/dllapi.hpp"

#ifdef SGEGUI_EXPORTS
	#define SGEGUIDLLAPI SGEDLLEXPORT
#else
	#define SGEGUIDLLAPI SGEDLLIMPORT
#endif

namespace sge
{
namespace gui
{

typedef space_unit             unit;
typedef sge::basic_rect<unit>  rect;

}
}

#endif
