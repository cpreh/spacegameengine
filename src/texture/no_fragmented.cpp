/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2011 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/guaranteed_free.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/texture/atlasing/bounds.hpp>
#include <sge/texture/atlasing/need.hpp>
#include <sge/texture/atlasing/size.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/resource_flags_none.hpp>
#include <sge/log/global.hpp>
#include <fcppt/math/dim/comparison.hpp>
#include <fcppt/math/dim/output.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <ostream>

sge::texture::no_fragmented::no_fragmented(
	renderer::device_ptr const _rend,
	image::color::format::type const _format,
	renderer::filter::texture const &_filter
)
:
 	rend_(_rend),
	format_(_format),
 	filter_(_filter)
{}

sge::texture::part_ptr const
sge::texture::no_fragmented::consume_fragment(
	renderer::dim2 const &_dim
)
{
	if(
		tex_
	)
		return part_ptr();

	renderer::dim2 const real_dim(
		atlasing::bounds(
			_dim
		)
	);

	tex_ =
		rend_->create_texture(
			real_dim,
			format_,
			filter_,
			renderer::resource_flags::none
		);

	if(
		real_dim != _dim
	)
		FCPPT_LOG_WARNING(
			log::global(),
			fcppt::log::_
				<< FCPPT_TEXT("You used a texture::no_fragmented whose dimensions are not a power of 2.")\
				FCPPT_TEXT(" This is slower to load and requires more texture memory because it needs atlasing and thus is not intuitive.")\
				FCPPT_TEXT(" The texture's size was ")
				<< _dim
				<< FCPPT_TEXT('.')
		);

	return
		part_ptr(
			fcppt::make_shared_ptr<
				part_fragmented
			>(
				renderer::lock_rect(
					renderer::lock_rect::vector::null(),
					atlasing::size(
						_dim
					)
				),
				std::tr1::ref(
					*this
				),
				atlasing::need(
					_dim.w()
				),
				atlasing::need(
					_dim.h()
				)
			)
		);
}

void
sge::texture::no_fragmented::on_return_fragment(
	part const &
)
{
	tex_.reset();
}

sge::renderer::texture_ptr const
sge::texture::no_fragmented::texture() const
{
	return tex_;
}

bool
sge::texture::no_fragmented::repeatable() const
{
	return true;
}

sge::texture::free_type
sge::texture::no_fragmented::free_value() const
{
	return empty() ? 0 : guaranteed_free();
}

bool
sge::texture::no_fragmented::empty() const
{
	return !tex_;
}
