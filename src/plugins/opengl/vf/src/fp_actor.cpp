#include "../fp_actor.hpp"
#include "../client_state_combiner.hpp"

sge::opengl::vf::fp_actor::fp_actor(
	vf::actor_parameters const &_param,
	GLenum const _client_state
)
:
	pointer_actor(
		_param
	),
	client_state_(
		_client_state
	)
{
}
		
void
sge::opengl::vf::fp_actor::operator()(
	client_state_combiner &_combiner,
	vf::pointer const _src
) const
{
	on_use(
		_src
	);

	_combiner.enable(
		client_state_
	);
}

void
sge::opengl::vf::fp_actor::unuse(
	client_state_combiner &_combiner
) const
{
	_combiner.disable(
		client_state_
	);
}
