#include <sge/projectile/shape/triangle_sequence.hpp>
#include <sge/projectile/shape/detail/index_container.hpp>
#include <sge/src/projectile/declare_local_logger.hpp>
#include <sge/src/projectile/shape/triangle_indices.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/verbose.hpp>


SGE_PROJECTILE_DECLARE_LOCAL_LOGGER(
	FCPPT_TEXT("triangle_indices")
)

sge::projectile::shape::detail::index_container
sge::projectile::shape::triangle_indices(
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
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("filled scalar container, now filling index container"));

	sge::projectile::shape::detail::index_container::iterator current_index_iterator(
		indices.begin()
	);

	sge::projectile::shape::detail::index_container::value_type current_index(
		0
	);

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
		local_log,
		fcppt::log::_
			<< FCPPT_TEXT("filled index container (last index was ") << current_index << FCPPT_TEXT("), now creating bullet shape"));

	return
		indices;
}
