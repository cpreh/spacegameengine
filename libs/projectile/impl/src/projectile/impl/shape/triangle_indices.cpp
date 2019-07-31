//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/projectile/impl/shape/triangle_indices.hpp>
#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/shape/detail/index_container.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/log/verbose.hpp>


sge::projectile::shape::detail::index_container
sge::projectile::impl::shape::triangle_indices(
	fcppt::log::object &_log,
	sge::projectile::shape::triangle_sequence const &_triangles
)
{
	sge::projectile::shape::detail::index_container indices(
		// Since we have to extrude each triangle separately (well,
		// technically we don't have to but this is a good compromise)
		// there are 8 output triangles per input triangle.
		_triangles.size() * 2u * 3u * 4u
	);

	FCPPT_LOG_DEBUG(
		_log,
		fcppt::log::out
			<< FCPPT_TEXT("filled scalar container, now filling index container")
	)

	sge::projectile::shape::detail::index_container::iterator current_index_iterator(
		indices.begin()
	);

	sge::projectile::shape::detail::index_container::value_type current_index(
		0
	);

	// TODO: Find a better way to express this
	while(current_index_iterator != indices.end())
	{
		// top
		*current_index_iterator++ = current_index+0;
		*current_index_iterator++ = current_index+1;
		*current_index_iterator++ = current_index+2;
		// bottom
		*current_index_iterator++ = current_index+3;
		*current_index_iterator++ = current_index+4;
		*current_index_iterator++ = current_index+5;

		// first side
		*current_index_iterator++ = current_index+0;
		*current_index_iterator++ = current_index+3;
		*current_index_iterator++ = current_index+4;

		*current_index_iterator++ = current_index+4;
		*current_index_iterator++ = current_index+1;
		*current_index_iterator++ = current_index+0;

		// second side
		*current_index_iterator++ = current_index+5;
		*current_index_iterator++ = current_index+2;
		*current_index_iterator++ = current_index+1;

		*current_index_iterator++ = current_index+1;
		*current_index_iterator++ = current_index+4;
		*current_index_iterator++ = current_index+5;

		// third side side
		*current_index_iterator++ = current_index+3;
		*current_index_iterator++ = current_index+0;
		*current_index_iterator++ = current_index+2;

		*current_index_iterator++ = current_index+2;
		*current_index_iterator++ = current_index+5;
		*current_index_iterator++ = current_index+3;

		current_index += 6;
	}

	FCPPT_LOG_DEBUG(
		_log,
		fcppt::log::out
			<<
			FCPPT_TEXT("filled index container (last index was ")
			<<
			current_index
			<<
			FCPPT_TEXT("), now creating bullet shape")
	)

	return
		indices;
}
