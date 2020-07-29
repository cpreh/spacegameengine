//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/element_count.hpp>
#include <sge/opengl/call.hpp>
#include <sge/opengl/check_state.hpp>
#include <sge/opengl/common.hpp>
#include <sge/opengl/convert/color_base_type_sge.hpp>
#include <sge/opengl/vf/actor_parameters_fwd.hpp>
#include <sge/opengl/vf/color_actor.hpp>
#include <sge/opengl/vf/convert_color_format.hpp>
#include <sge/opengl/vf/fp_actor.hpp>
#include <sge/opengl/vf/pointer.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/cast/to_signed.hpp>


sge::opengl::vf::color_actor::color_actor(
	sge::opengl::vf::actor_parameters const &_param,
	sge::renderer::vf::dynamic::color const &_color
)
:
	sge::opengl::vf::fp_actor(
		_param,
		GL_COLOR_ARRAY
	),
	elements_(
		fcppt::cast::size<
			GLint
		>(
			fcppt::cast::to_signed(
				sge::image::color::element_count(
					_color.color_format()
				)
			)
		)
	),
	format_(
		sge::opengl::convert::color_base_type_sge(
			sge::opengl::vf::convert_color_format(
				_color.color_format()
			)
		)
	)
{
}

sge::opengl::vf::color_actor::~color_actor()
= default;

void
sge::opengl::vf::color_actor::on_use(
	sge::opengl::vf::pointer const _src
) const
{
	sge::opengl::call(
		::glColorPointer,
		elements_,
		format_.get(),
		fcppt::cast::size<
			GLsizei
		>(
			fcppt::cast::to_signed(
				this->stride().get()
			)
		),
		_src
	);

	SGE_OPENGL_CHECK_STATE(
		FCPPT_TEXT("glColorPointer failed"),
		sge::renderer::exception
	)
}
