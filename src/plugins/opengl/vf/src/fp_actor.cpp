#include "../fp_actor.hpp"
#include "../client_state_combiner.hpp"

sge::opengl::vf::fp_actor::fp_actor(
	renderer::vf::dynamic::ordered_element const &elem_,
	renderer::vf::vertex_size const stride_,
	GLenum const client_state_
)
:
	pointer_actor(
		elem_,
		stride_
	),
	client_state_(
		client_state_
	)
{
}
		
void
sge::opengl::vf::fp_actor::operator()(
	client_state_combiner &combiner_
) const
{
	on_use();

	combiner_.enable(
		client_state_
	);
}

void
sge::opengl::vf::fp_actor::unuse(
	client_state_combiner &combiner_
) const
{
	combiner_.disable(
		client_state_
	);
}
