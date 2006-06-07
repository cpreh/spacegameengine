#ifndef SGE_GUI_LINE_STRIP_HPP_INCLUDED
#define SGE_GUI_LINE_STRIP_HPP_INCLUDED

#include <vector>
#include "../core/renderer/renderer.hpp"
#include "../core/renderer/vertex_buffer.hpp"
#include "../core/renderer/index_buffer.hpp"
#include "./types.hpp"

namespace sge
{
namespace gui
{
	class line_strip {
	public:
		typedef std::vector<point> point_array;
		typedef point_array::size_type size_type;
		SGEGUIDLLAPI line_strip(const point_array& points, color line_color, renderer_ptr rend);
		SGEGUIDLLAPI line_strip(size_type sz, color line_color, renderer_ptr rend);
		SGEGUIDLLAPI point& operator[](size_type sz);
		SGEGUIDLLAPI const point& operator[](size_type sz) const;
		SGEGUIDLLAPI void draw();
		SGEGUIDLLAPI void update();
		SGEGUIDLLAPI void restore();
		color line_color;
	private:
		void init();
		point_array points;
		renderer_ptr rend;
		vertex_buffer_ptr vb;
		index_buffer_ptr ib;
	};
}
}
#endif
