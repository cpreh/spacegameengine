/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2012 Carl Philipp Reh (sefi@s-e-f-i.de)

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/


#include <sge/opengl/glx/visual/attribute_container.hpp>
#include <sge/opengl/glx/visual/convert_bit_depth.hpp>
#include <sge/opengl/glx/visual/make_attributes.hpp>
#include <sge/opengl/glx/visual/rgb_triple.hpp>
#include <sge/renderer/depth_buffer_bits.hpp>
#include <sge/renderer/multi_samples.hpp>
#include <sge/renderer/no_multi_sampling.hpp>
#include <sge/renderer/optional_bit_count.hpp>
#include <sge/renderer/parameters.hpp>
#include <sge/renderer/screen_mode_bit_depth.hpp>
#include <sge/renderer/stencil_buffer_bits.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <GL/glx.h>
#include <fcppt/config/external_end.hpp>


sge::opengl::glx::visual::attribute_container const
sge::opengl::glx::visual::make_attributes(
	sge::renderer::parameters const &_parameters
)
{
	sge::opengl::glx::visual::attribute_container ret;

	ret.push_back(
		GLX_RGBA
	);

	ret.push_back(
		GLX_DOUBLEBUFFER
	);

	{
		sge::opengl::glx::visual::rgb_triple const rgb(
			sge::opengl::glx::visual::convert_bit_depth(
				sge::renderer::screen_mode_bit_depth(
					_parameters.screen_mode()
				)
			)
		);

		ret.push_back(
			GLX_RED_SIZE
		);

		ret.push_back(
			rgb.red().get()
		);

		ret.push_back(
			GLX_BLUE_SIZE
		);

		ret.push_back(
			rgb.blue().get()
		);

		ret.push_back(
			GLX_GREEN_SIZE
		);

		ret.push_back(
			rgb.green().get()
		);
	}

	{
		sge::renderer::optional_bit_count const depth_bits(
			sge::renderer::depth_buffer_bits(
				_parameters.depth_stencil_buffer()
			)
		);

		if(
			depth_bits
		)
		{
			ret.push_back(
				GLX_DEPTH_SIZE
			);

			ret.push_back(
				static_cast<
					int
				>(
					depth_bits->get()
				)
			);
		}
	}

	{
		sge::renderer::optional_bit_count const stencil_bits(
			sge::renderer::stencil_buffer_bits(
				_parameters.depth_stencil_buffer()
			)
		);

		if(
			stencil_bits
		)
		{
			ret.push_back(
				GLX_STENCIL_SIZE
			);

			ret.push_back(
				static_cast<
					int
				>(
					stencil_bits->get()
				)
			);
		}
	}

	{
		sge::renderer::multi_samples const samples(
			_parameters.samples()
		);

		if(
			samples
			!=
			sge::renderer::no_multi_sampling
		)
		{
			ret.push_back(
				GLX_SAMPLE_BUFFERS
			);

			ret.push_back(
				1
			);

			ret.push_back(
				GLX_SAMPLES
			);

			ret.push_back(
				static_cast<
					int
				>(
					samples.get()
				)
			);
		}
	}

	ret.push_back(
		None
	);

	return
		ret;
}
