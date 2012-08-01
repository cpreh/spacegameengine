#include <sge/graph/object.hpp>
#include <sge/graph/scalar.hpp>
#include <sge/image/color/format.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/image/colors.hpp>
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
#include <iostream>
#include <ostream>
#include <cmath>
#include <boost/circular_buffer.hpp>
#include <boost/algorithm/minmax_element.hpp>
#include <fcppt/config/external_end.hpp>
#include <fcppt/math/clamp.hpp>


namespace
{
sge::graph::scalar
normalize(
	sge::graph::scalar const &t,
	sge::graph::scalar const &min,
	sge::graph::scalar const &max
)
{
	return
		(t - min) /
		(max - min);
}

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
	_color,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	_corner1,
	sge::image2d::vector(_corner2.x(), _corner1.y()),
	_color,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	sge::image2d::vector(_corner1.x(), _corner2.y()),
	_corner2,
	_color,
	_color
);
sge::image2d::algorithm::bresenham(
	_view,
	sge::image2d::vector(_corner2.x(), _corner1.y()),
	_corner2,
	_color,
	_color
);
}

}

sge::graph::object::object(
	sge::renderer::dim2 const &_dim,
	sge::renderer::device &_renderer,
	sge::image::color::any::object const &_foreground_color,
	sge::image::color::any::object const &_background_color,
	sge::graph::scalar _baseline
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
				sge::renderer::texture::capabilities_field::null()
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
baseline_(
	_baseline),
current_min_(
	std::min(
		0.,
		baseline_)
	),
current_max_(
	1. +
	std::max(
		current_min_,
		baseline_)
	)
{
	sge::renderer::texture::scoped_planar_lock lock(
		*texture_,
		sge::renderer::lock_mode::writeonly);

	clear(
		lock.value());
}

void
sge::graph::object::push(
	sge::graph::scalar _datum)
{
	data_buffer_.push_back(
		_datum);

	typedef
	buffer_type::iterator
	iterator_type;

	std::pair<iterator_type, iterator_type>
	minmax(
		boost::minmax_element(
			data_buffer_.begin(),
			data_buffer_.end()
	));

	current_min_ = *(minmax.first);
	current_max_ = *(minmax.second);
}

void
sge::graph::object::render(
	sge::renderer::context::object &_context)
{
	sge::renderer::texture::scoped_planar_lock lock(
		*texture_,
		sge::renderer::lock_mode::writeonly);

	draw_data(lock.value());

	sge::sprite::process::one(
		_context,
		sprite_object_,
		sprite_buffers_
	);
}

void
sge::graph::object::clear(
	sge::image2d::view::object const _view
)
{
	sge::image2d::algorithm::fill(
		_view,
		background_color_
	);

	draw_rectangle(
		_view,
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
sge::graph::object::draw_data(
	sge::image2d::view::object const _view
)
{
	clear(
		_view);

	unsigned const baseline =
		static_cast<
			unsigned
		>(
			fcppt::math::clamp(
				(
				 static_cast<int>(
					static_cast<
						sge::graph::scalar
					>
					(
						dim_.h() - 1
					)
					*
					(
					1.0
					-
					normalize(
						baseline_,
						current_min_,
						current_max_)
					)
				)),
				0,
				static_cast<int>(dim_.h() - 1))
		);

	unsigned const zero =
		static_cast<
			unsigned
		>
		(
		 	fcppt::math::clamp(
				static_cast<int>(
				static_cast<
					sge::graph::scalar
				>
				(
					dim_.h() - 1
				)
				*
				(
				1.0
				-
				normalize(
					0.,
					current_min_,
					current_max_)
				)),
				0,
				static_cast<int>(dim_.h() - 1))
		);

	for (unsigned i = 0; i < data_buffer_.size(); ++i)
	{
		unsigned const value =
			static_cast<
				unsigned
			>
			(
				static_cast<
					sge::graph::scalar
				>
				(
					dim_.h() - 1
				)
				*
				// normalize data point
				normalize(
					data_buffer_[i],
					current_min_,
					current_max_)
			);

		bool const above = data_buffer_[i] > 0.;

		sge::image2d::algorithm::bresenham(
			_view,
			sge::image2d::vector(
				i,
				zero
			),
			sge::image2d::vector(
				i,
				dim_.h() - 1 - value
			),
			above ? background_color_ : foreground_color_,
			above ? foreground_color_ : background_color_
		);
	}

	// zero line
	if (zero >= 0 && zero < dim_.h())
		sge::image2d::algorithm::bresenham(
			_view,
			sge::image2d::vector(
				0,
				zero
			),
			sge::image2d::vector(
				dim_.w() - 1,
				zero
			),
			foreground_color_,
			foreground_color_
		);

	// baseline
	sge::image2d::algorithm::bresenham(
		_view,
		sge::image2d::vector(
			0,
			baseline
		),
		sge::image2d::vector(
			dim_.w() - 1,
			baseline
		),
		sge::image::colors::yellow(),
		sge::image::colors::yellow()
	);

}

sge::graph::object::~object()
{
}
