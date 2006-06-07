#include "../line.hpp"
#include "../transform.hpp"
#include "../../core/renderer/lock_ptr.hpp"

sge::gui::line::line(const point p1, const point p2, const color line_color, const renderer_ptr rend)
: p1(p1), p2(p2), line_color(line_color), rend(rend)
{
	vb = rend->create_vertex_buffer(vertex_format().add(VU_Pos),2,RF_AutoRestore);
	recalc_vertices();
}

void sge::gui::line::draw()
{
	rend->set_int_state(IS_AmbientLightColor,line_color);
	rend->set_texture_stage_op(  0, SOP_Color,   SOPV_SelectArg1 );
	rend->set_texture_stage_arg( 0, SARG_Color1, SARGV_Diffuse );
	rend->set_texture_stage_op(1,SOP_Color,SOPV_Disable);
	rend->set_matrix(MU_Transform,matrix4x4<space_unit>());
	rend->set_matrix(MU_Camera,matrix4x4<space_unit>());
	rend->set_matrix(MU_Projection,matrix4x4<space_unit>());
	rend->render(vb,index_buffer_ptr(),0,2,PT_LineStrip,1,0);
}

void sge::gui::line::recalc_vertices()
{
	lock_ptr<vertex_buffer> l(vb.get());
	vertex_buffer::iterator it = vb->begin();
	(*it++).pos() = gui_to_space(p1);
	(*it  ).pos() = gui_to_space(p2);
}
