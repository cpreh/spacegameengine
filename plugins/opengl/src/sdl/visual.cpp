//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opengl/sdl/visual.hpp>
#include <sge/opengl/visual/convert_color.hpp>
#include <sge/opengl/visual/rgb_triple.hpp>
#include <sge/renderer/exception.hpp>
#include <sge/renderer/unsupported.hpp>
#include <sge/renderer/pixel_format/bit_count.hpp>
#include <sge/renderer/pixel_format/depth_bits.hpp>
#include <sge/renderer/pixel_format/object.hpp>
#include <sge/renderer/pixel_format/srgb.hpp>
#include <sge/renderer/pixel_format/stencil_bits.hpp>
#include <awl/backends/sdl/visual/flags.hpp>
#include <awl/backends/sdl/visual/object.hpp>
#include <fcppt/not.hpp>
#include <fcppt/output_to_fcppt_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/enum_to_underlying.hpp>
#include <fcppt/cast/to_signed.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/config/external_begin.hpp>
#include <SDL_video.h>
#include <fcppt/config/external_end.hpp>


namespace
{

[[nodiscard]]
bool
set_attribute_maybe(
	SDL_GLattr const _attr,
	int const _value
)
{
	return
		SDL_GL_SetAttribute(
			_attr,
			_value
		)
		==
		0;
}

}


sge::opengl::sdl::visual::visual(
	sge::renderer::pixel_format::object const &_pixel_format
)
:
	awl::backends::sdl::visual::object{
		awl::backends::sdl::visual::flags{
			SDL_WINDOW_OPENGL
		}
	},
	pixel_format_{
		_pixel_format
	}
{
}

sge::opengl::sdl::visual::~visual()
{
}

void
sge::opengl::sdl::visual::apply() const
{
	auto const set_attribute(
		[](
			SDL_GLattr const _attr,
			int const _value
		)
		{
			if(
				fcppt::not_(
					set_attribute_maybe(
						_attr,
						_value
					)
				)
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("Failed to set SDL GL attribute ")
						+
						fcppt::output_to_fcppt_string(
							fcppt::cast::enum_to_underlying(
								_attr
							)
						)
						+
						FCPPT_TEXT(" to ")
						+
						fcppt::output_to_fcppt_string(
							_value
						)
						+
						FCPPT_TEXT("!")
					};
		}
	);

	set_attribute(
		SDL_GL_DOUBLEBUFFER,
		1
	);

	{
		sge::opengl::visual::rgb_triple const rgb(
			sge::opengl::visual::convert_color(
				this->pixel_format_.color()
			)
		);

		set_attribute(
			SDL_GL_RED_SIZE,
			rgb.red().get()
		);

		set_attribute(
			SDL_GL_BLUE_SIZE,
			rgb.blue().get()
		);

		set_attribute(
			SDL_GL_GREEN_SIZE,
			rgb.green().get()
		);
	}

	fcppt::optional::maybe_void(
		sge::renderer::pixel_format::depth_bits(
			this->pixel_format_.depth_stencil()
		),
		[
			&set_attribute
		](
			sge::renderer::pixel_format::bit_count const _depth_bits
		)
		{
			set_attribute(
				SDL_GL_DEPTH_SIZE,
				fcppt::cast::to_signed(
					_depth_bits.get()
				)
			);
		}
	);

	fcppt::optional::maybe_void(
		sge::renderer::pixel_format::stencil_bits(
			this->pixel_format_.depth_stencil()
		),
		[
			&set_attribute
		](
			sge::renderer::pixel_format::bit_count const _depth_bits
		)
		{
			set_attribute(
				SDL_GL_STENCIL_SIZE,
				fcppt::cast::to_signed(
					_depth_bits.get()
				)
			);
		}
	);

	fcppt::optional::maybe_void(
		this->pixel_format_.multi_samples(),
		[
			&set_attribute
		](
			sge::renderer::pixel_format::multi_samples const _samples
		)
		{
			set_attribute(
				SDL_GL_MULTISAMPLESAMPLES,
				fcppt::cast::to_signed(
					_samples.get()
				)
			);
		}
	);

	{
		auto const set_srgb(
			[]{
				return
					set_attribute_maybe(
						SDL_GL_FRAMEBUFFER_SRGB_CAPABLE,
						1
					);
			}
		);

		switch(
			this->pixel_format_.srgb()
		)
		{
		case sge::renderer::pixel_format::srgb::no:
			break;
		case sge::renderer::pixel_format::srgb::yes:
			if(
				fcppt::not_(
					set_srgb()
				)
			)
				throw
					sge::renderer::unsupported{
						FCPPT_TEXT("SDL_GL_FRAMEBUFFER_SRGB_CAPABLE"),
						FCPPT_TEXT(""),
						FCPPT_TEXT("")
					};
			break;
		case sge::renderer::pixel_format::srgb::try_:
			set_srgb();
			break;
		}
	}
}
