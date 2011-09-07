#include "opencl_color_format_to_sge.hpp"
#include <sge/opencl/memory_object/read_planar_texture.hpp>
#include <sge/opencl/memory_object/planar_texture.hpp>
#include <sge/opencl/command_queue/scoped_planar_mapping.hpp>
#include <sge/image/algorithm/may_overlap.hpp>
#include <sge/image/raw_pointer.hpp>
#include <sge/image2d/view/const_object.hpp>
#include <sge/image2d/algorithm/copy_and_convert.hpp>
#include <sge/image2d/view/make_const.hpp>
#include <sge/image2d/view/make.hpp>
#include <sge/image2d/dim.hpp>
#include <sge/image2d/pitch.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/optional_impl.hpp>

void
sge::opencl::memory_object::read_planar_texture(
	opencl::command_queue::object &_queue,
	opencl::memory_object::planar_texture const &_image,
	sge::image2d::view::object const &_view,
	opencl::memory_object::rect const &_rect)
{
	command_queue::scoped_planar_mapping scoped_map(
		_queue,
		const_cast<opencl::memory_object::planar_texture &>(
			_image),
		CL_MAP_READ,
		_rect);

	sge::image2d::algorithm::copy_and_convert(
		sge::image2d::view::make_const(
			static_cast<sge::image::raw_pointer>(
				scoped_map.ptr()),
			fcppt::math::dim::structure_cast<sge::image2d::dim>(
				_rect.size()),
			memory_object::opencl_color_format_to_sge(
				_image.image_format()),
			image2d::pitch(
				static_cast<image2d::pitch::value_type>(
					scoped_map.pitch()))),
		_view,
		sge::image::algorithm::may_overlap::yes);
}
