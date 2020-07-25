//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/any/compare.hpp>
#include <sge/image/color/any/object_fwd.hpp>
#include <sge/scenic/render_context/ambient_color.hpp>
#include <sge/scenic/render_context/diffuse_color.hpp>
#include <sge/scenic/render_context/emissive_color.hpp>
#include <sge/scenic/render_context/specular_color.hpp>
#include <sge/scenic/render_context/material/diffuse_texture.hpp>
#include <sge/scenic/render_context/material/object.hpp>
#include <sge/scenic/render_context/material/shininess.hpp>
#include <sge/scenic/render_context/material/specular_texture.hpp>
#include <fcppt/reference_comparison.hpp>
#include <fcppt/optional/comparison.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <type_traits>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

bool
compare_floats(
	float const _a,
	float const _b
)
{
	return
		std::abs(_a - _b) < 0.001F; // NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}

struct compare_channels
{
	template<
		typename T
	>
	std::enable_if_t<
		std::is_integral<
			T
		>::value,
		bool
	>
	operator()(
		T const _a,
		T const _b
	) const
	{
		return
			_a
			==
			_b;
	}

	bool
	operator()(
		float const _a,
		float const _b
	) const
	{
		return
			compare_floats(
				_a,
				_b
			);
	}
};

template<
	typename T
>
bool
compare_colors(
	T const &_a,
	T const &_b
)
{
	return
		sge::image::color::any::compare(
			_a.get(),
			_b.get(),
			compare_channels()
		);
}

}

sge::scenic::render_context::material::object::object(
	sge::scenic::render_context::diffuse_color _diffuse_color,
	sge::scenic::render_context::ambient_color _ambient_color,
	sge::scenic::render_context::specular_color _specular_color,
	sge::scenic::render_context::emissive_color _emissive_color,
	sge::scenic::render_context::material::shininess const &_shininess,
	sge::scenic::render_context::material::diffuse_texture const &_diffuse_texture,
	sge::scenic::render_context::material::specular_texture const &_specular_texture)
:
	diffuse_color_(
		std::move(
			_diffuse_color
		)
	),
	ambient_color_(
		std::move(
			_ambient_color
		)
	),
	specular_color_(
		std::move(
			_specular_color
		)
	),
	emissive_color_(
		std::move(
			_emissive_color
		)
	),
	shininess_(
		_shininess
	),
	diffuse_texture_(
		_diffuse_texture
	),
	specular_texture_(
		_specular_texture
	)
{
}

sge::scenic::render_context::diffuse_color const &
sge::scenic::render_context::material::object::diffuse_color() const
{
	return
		diffuse_color_;
}

sge::scenic::render_context::ambient_color const &
sge::scenic::render_context::material::object::ambient_color() const
{
	return
		ambient_color_;
}

sge::scenic::render_context::specular_color const &
sge::scenic::render_context::material::object::specular_color() const
{
	return
		specular_color_;
}

sge::scenic::render_context::emissive_color const &
sge::scenic::render_context::material::object::emissive_color() const
{
	return
		emissive_color_;
}

sge::scenic::render_context::material::shininess const &
sge::scenic::render_context::material::object::shininess() const
{
	return
		shininess_;
}

sge::scenic::render_context::material::diffuse_texture const &
sge::scenic::render_context::material::object::diffuse_texture() const
{
	return
		diffuse_texture_;
}

sge::scenic::render_context::material::specular_texture const &
sge::scenic::render_context::material::object::specular_texture() const
{
	return
		specular_texture_;
}

bool
sge::scenic::render_context::material::object::operator==(
	sge::scenic::render_context::material::object const &_right) const
{
	return
		compare_colors(
			diffuse_color_,
			_right.diffuse_color_
		)
		&&
		compare_colors(
			ambient_color_,
			_right.ambient_color_
		)
		&&
		compare_colors(
			specular_color_,
			_right.specular_color_
		)
		&&
		compare_colors(
			emissive_color_,
			_right.emissive_color_
		)
		&&
		compare_floats(
			shininess_.get(),
			_right.shininess_.get()
		)
		&&
		diffuse_texture_
		==
		_right.diffuse_texture_
		&&
		specular_texture_
		==
		_right.specular_texture_
		;
}
