//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/common.hpp>
#include <sge/opengl/disable_client_state.hpp>
#include <sge/opengl/enable_client_state.hpp>
#include <sge/opengl/context/object.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/opengl/vf/attribute_context.hpp>
#include <sge/opengl/vf/client_state_combiner.hpp>
#include <sge/opengl/vf/context.hpp>
#include <sge/opengl/vf/disable_texcoords.hpp>
#include <sge/opengl/vf/disable_vertex_attrib_array.hpp>
#include <sge/opengl/vf/enable_texcoords.hpp>
#include <sge/opengl/vf/enable_vertex_attrib_array.hpp>
#include <sge/renderer/texture/stage.hpp>
#include <fcppt/container/set_difference.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <functional>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void
apply_difference(
	Set const &old_states,
	Set const &new_states,
	EnableFun,
	DisableFun
);

}

sge::opengl::vf::client_state_combiner::client_state_combiner(
	fcppt::log::object &_log,
	sge::opengl::context::object &_context
)
:
	log_{
		_log
	},
	context_(
		_context
	),
	vf_context_(
		sge::opengl::context::use<
			sge::opengl::vf::context
		>(
			_context,
			_log
		)
	),
	attribute_context_(
		sge::opengl::context::use<
			sge::opengl::vf::attribute_context
		>(
			_context,
			_context.info()
		)
	),
	old_states_(
		vf_context_.state()
	),
	new_states_(
		old_states_
	)
{
}

void
sge::opengl::vf::client_state_combiner::enable(
	GLenum const _enum
)
{
	new_states_.enable(
		_enum
	);
}

void
sge::opengl::vf::client_state_combiner::disable(
	GLenum const _enum
)
{
	new_states_.disable(
		_enum
	);
}

void
sge::opengl::vf::client_state_combiner::enable_texture(
	sge::renderer::texture::stage const _texture
)
{
	new_states_.enable_texture(
		_texture
	);
}

void
sge::opengl::vf::client_state_combiner::disable_texture(
	sge::renderer::texture::stage const _texture
)
{
	new_states_.disable_texture(
		_texture
	);
}

void
sge::opengl::vf::client_state_combiner::enable_attribute(
	GLuint const _attribute
)
{
	new_states_.enable_attribute(
		_attribute
	);
}

void
sge::opengl::vf::client_state_combiner::disable_attribute(
	GLuint const _attribute
)
{
	new_states_.disable_attribute(
		_attribute
	);
}

sge::opengl::vf::client_state_combiner::~client_state_combiner()
{
	apply_difference(
		old_states_.normal_states(),
		new_states_.normal_states(),
		sge::opengl::enable_client_state,
		sge::opengl::disable_client_state
	);

	apply_difference(
		old_states_.texture_states(),
		new_states_.texture_states(),
		std::bind(
			sge::opengl::vf::enable_texcoords,
			std::ref(
				log_
			),
			std::ref(
				context_
			),
			std::placeholders::_1
		),
		std::bind(
			sge::opengl::vf::disable_texcoords,
			std::ref(
				log_
			),
			std::ref(
				context_
			),
			std::placeholders::_1
		)
	);

	apply_difference(
		old_states_.attribute_states(),
		new_states_.attribute_states(),
		std::bind(
			sge::opengl::vf::enable_vertex_attrib_array,
			std::ref(
				attribute_context_
			),
			std::placeholders::_1
		),
		std::bind(
			sge::opengl::vf::disable_vertex_attrib_array,
			std::ref(
				attribute_context_
			),
			std::placeholders::_1
		)
	);

	vf_context_.state(
		new_states_
	);
}

namespace
{

template<
	typename Set,
	typename EnableFun,
	typename DisableFun
>
void
apply_difference(
	Set const &_old_states,
	Set const &_new_states,
	EnableFun const _enable,
	DisableFun const _disable
)
{
	for(
		auto const &element
		:
		fcppt::container::set_difference(
			_old_states,
			_new_states
		)
	)
		_disable(
			element
		);

	for(
		auto const &element
		:
		fcppt::container::set_difference(
			_new_states,
			_old_states
		)
	)
		_enable(
			element
		);
}

}
