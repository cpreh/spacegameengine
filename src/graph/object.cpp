#include <sge/graph/object.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image2d/vector.hpp>
#include <sge/image2d/algorithm/bresenham.hpp>
#include <sge/image2d/algorithm/fill.hpp>
#include <sge/image2d/view/object.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/dim2.hpp>
#include <sge/renderer/lock_mode.hpp>
#include <sge/renderer/resource_flags_field.hpp>
#include <sge/renderer/context/object.hpp>
#include <sge/renderer/texture/capabilities.hpp>
#include <sge/renderer/texture/capabilities_field.hpp>
#include <sge/renderer/texture/planar.hpp>
#include <sge/renderer/texture/planar_parameters.hpp>
#include <sge/renderer/texture/planar_scoped_ptr.hpp>
#include <sge/renderer/texture/scoped_planar_lock.hpp>
#include <sge/renderer/texture/mipmap/off.hpp>
#include <sge/sprite/buffers/option.hpp>
#include <sge/sprite/process/one.hpp>
#include <sge/texture/part_raw_ref.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/circular_buffer.hpp>
#include <iostream>
#include <fcppt/config/external_end.hpp>


namespace
{
void
draw_rectangle(
	sge::image2d::view::object const &_view,
	sge::image2d::vector const &_corner1,
	sge::image2d::vector const &_corner2,
	sge::image::color::any::object const &_color
)
{
sge::image2d::algorithm::bresenham(
	_view,
	_corner1,
	sge::image2d::vector(_corner1.x(), _corner2.y()),
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	_corner1,
	sge::image2d::vector(_corner2.x(), _corner1.y()),
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	sge::image2d::vector(_corner1.x(), _corner2.y()),
	_corner2,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	sge::image2d::vector(_corner2.x(), _corner1.y()),
	_corner2,
	_color
);
}

}

sge::graph::object::object(
	sge::renderer::dim2 const &_dim,
	sge::renderer::device &_renderer,
	sge::image::color::any::object const &_foreground_color,
	sge::image::color::any::object const &_background_color
)
:
dim_(
	_dim),
texture_(
	_renderer.create_planar_texture(
		sge::renderer::texture::planar_parameters(
			_dim,
			sge::image::color::format::rgba8,
			sge::renderer::texture::mipmap::off(),
			sge::renderer::resource_flags_field::null(),
			sge::renderer::texture::capabilities_field(
				sge::renderer::texture::capabilities::render_target
			)
		)
	)
),
sprite_object_(
	sprite_parameters()
	.pos(
		sprite_object::vector::null()
	)
	.texture(
		fcppt::make_shared_ptr<
			sge::texture::part_raw_ref
		>(
			fcppt::ref(
				*texture_
			)
		)
	)
	.texture_size()
),
sprite_buffers_(
	_renderer,
	sge::sprite::buffers::option::dynamic
),
foreground_color_(
	_foreground_color),
background_color_(
	_background_color),
data_buffer_(
	dim_.w()),
current_max_(
	0.)
{
	clear();
}

void
sge::graph::object::push(
	sge::graph::scalar _datum)
{
	data_buffer_.push_back(
		_datum);
	if (_datum > current_max_)
		current_max_ = _datum;
}

void
sge::graph::object::render(
	sge::renderer::context::object &_context)
{
	draw_data();
	sge::sprite::process::one(
		_context,
		sprite_object_,
		sprite_buffers_
	);
}

void
sge::graph::object::clear()
{
	sge::renderer::texture::scoped_planar_lock lock(
		*texture_,
		sge::renderer::lock_mode::writeonly);

	sge::image2d::algorithm::fill(
		lock.value(),
		background_color_
	);
	draw_rectangle(
		lock.value(),
		sge::image2d::vector(
			0,
			0
		),
		sge::image2d::vector(
			dim_.w() - 1,
			dim_.h() - 1
		),
		foreground_color_
	);
}

void
sge::graph::object::draw_data()
{
	clear();

	sge::renderer::texture::scoped_planar_lock lock(
		*texture_,
		sge::renderer::lock_mode::writeonly);

	for (unsigned i = 0; i < data_buffer_.size(); ++i)
	{
		unsigned foo = static_cast<unsigned>(static_cast<sge::graph::scalar>(dim_.h()) * data_buffer_[i]/current_max_);
		// std::cout << foo << '\t';
		sge::image2d::algorithm::bresenham(
			lock.value(),
			sge::image2d::vector(
				i,
				0u
			),
			sge::image2d::vector(
				i,
				foo
			),
			foreground_color_
		);
	}
}

sge::graph::object::~object()
{
}
