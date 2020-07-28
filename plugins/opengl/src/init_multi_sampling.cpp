//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/enable.hpp>
#include <sge/opengl/init_multi_sampling.hpp>
#include <sge/opengl/multi_sample_context.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/use.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/optional_multi_samples.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>


void
sge::opengl::init_multi_sampling(
	sge::opengl::context::object &_context,
	sge::renderer::pixel_format::optional_multi_samples const &_samples
)
{
	if(
		!_samples.has_value()
	)
	{
		return;
	}

	sge::opengl::multi_sample_context const &multi_sample_context(
		sge::opengl::context::use<
			sge::opengl::multi_sample_context
		>(
			fcppt::make_ref(
				_context
			),
			_context.info()
		)
	);

	sge::opengl::enable(
		fcppt::optional::to_exception(
			multi_sample_context.flag(),
			[]{
				return
					sge::renderer::unsupported{
						FCPPT_TEXT("multi sampling"),
						FCPPT_TEXT("GL_VERSION_1_3"),
						FCPPT_TEXT("GL_ARB_multisample")
					};
			}
		)
	);
}
