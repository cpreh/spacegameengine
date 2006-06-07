#ifndef SGE_GUI_LINE_HPP_INCLUDED
#define SGE_GUI_LINE_HPP_INCLUDED

#include "../core/renderer/renderer.hpp"
#include "../core/renderer/vertex_buffer.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui
{
	class line {
	public:
		SGEGUIDLLAPI line(point p1, point p2, color line_color, renderer_ptr rend);
		SGEGUIDLLAPI void draw();
		point p1, p2;
		color line_color;
	private:
		void recalc_vertices();
		renderer_ptr          rend;
		vertex_buffer_ptr     vb;
	};
}
}

#endif
