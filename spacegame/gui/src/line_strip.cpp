#include "../line_strip.hpp"
#include "../transform.hpp"
#include "../../core/renderer/lock_ptr.hpp"

sge::gui::line_strip::line_strip(const size_type sz, const color line_color, const renderer_ptr rend)
: line_color(line_color), points(sz), rend(rend)
{
	init();
}

sge::gui::line_strip::line_strip(const point_array& points, const color line_color, const renderer_ptr rend)
: line_color(line_color), points(points), rend(rend)
{
	init();
}

void sge::gui::line_strip::init()
{
	vb = rend->create_vertex_buffer(create_vertex_format().add(VU_Pos),points.size());
	ib = rend->create_index_buffer(points.size()*2);
	lock_ptr<index_buffer> l(ib.get());
	{
		index_buffer::iterator it = ib->begin();
		unsigned i;
		for(i = 0; i < points.size()-1; ++i)
		{
			(*it++) = i;
			(*it++) = i+1;
		}
		(*it++) = i;
		(*it  ) = 0;
	}
	update();
}

void sge::gui::line_strip::update()
{
	lock_ptr<vertex_buffer> l(vb.get());
	vertex_buffer::iterator it = vb->begin();
	for(unsigned i = 0; i < points.size(); ++i)
		(*it++).pos() = gui_to_space(points[i]);
}

void sge::gui::line_strip::draw()
{
	rend->set_int_state(IS_AmbientLightColor,line_color);
	rend->set_texture_stage_op(  0, SOP_Color,   SOPV_SelectArg1 );
	rend->set_texture_stage_arg( 0, SARG_Color1, SARGV_Diffuse   );
	rend->set_texture_stage_op(  1, SOP_Color,   SOPV_Disable    );
	rend->set_material(material(color4(1,1,1,1),color4(1,1,1,1)));
	rend->set_texture(0,texture_ptr());
	rend->render(vb,ib,0,vb->size(),PT_Line,points.size());
}

void sge::gui::line_strip::restore()
{
	init();
}

sge::point& sge::gui::line_strip::operator [](const size_type sz) { return points[sz]; }
const sge::point& sge::gui::line_strip::operator [](const size_type sz) const { return points[sz]; }

