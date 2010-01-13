/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2009 Carl Philipp Reh (sefi@s-e-f-i.de)

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


#include <sge/texture/cell_fragmented.hpp>
#include <sge/texture/atlasing/create_texture.hpp>
#include <sge/texture/atlasing/texture_dim.hpp>
#include <sge/texture/part_fragmented.hpp>
#include <sge/exception.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/box/basic_impl.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/container/field_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_shared_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert.hpp>
#include <algorithm>

sge::texture::cell_fragmented::cell_fragmented(
	renderer::device_ptr const rend,
	image::color::format::type const format,
	renderer::filter::texture const &filter,
	renderer::dim_type const &cell_size
)
:
	rend(rend),
	cell_size(cell_size),
	cells(
		atlasing::texture_dim(rend) / cell_size,
		false
	),
	tex(
		atlasing::create_texture(
			rend,
			format,
			filter
		)
	)
{}

sge::texture::cell_fragmented::~cell_fragmented()
{}

sge::texture::part_ptr const
sge::texture::cell_fragmented::consume_fragment(
	renderer::dim_type const &dim
)
{
	if(dim != cell_size)
		throw exception(
			FCPPT_TEXT("Invalid request for consume_fragments in texture::cell_fragmented!")
		);

	// TODO maybe optimize this with a stack?
	field_type::iterator const it(
		std::find(
			cells.begin(),
			cells.end(),
			false
		)
	);

	if(it == cells.end())
		return part_ptr();

	*it = true;

	field_type::vector const pos(
		cells.position(it)
	);

	return
		fcppt::make_shared_ptr<
			part_fragmented
		>(
			renderer::lock_rect(
				pos + cell_size,
				cell_size
			),
			std::tr1::ref(
				*this
			),
			true,
			true
		);
}

void
sge::texture::cell_fragmented::on_return_fragment(
	part const &t
)
{
	field_type::vector const pos(
		t.area().pos() * cell_size
	);

	FCPPT_ASSERT(cells.pos(pos));

	cells.pos(pos) = false;
}

sge::renderer::texture_ptr const
sge::texture::cell_fragmented::texture() const
{
	return tex;
}

bool
sge::texture::cell_fragmented::repeatable() const
{
	return false;
}

sge::texture::free_type
sge::texture::cell_fragmented::free_value() const
{
	return empty() ? 0 : cell_size.content();
}

bool
sge::texture::cell_fragmented::empty() const
{
	return
		std::find(
			cells.begin(),
			cells.end(),
			false
		) == cells.end(); // TODO: optimize this!
}
