/*
spacegameengine is a portable easy to use game engine written in C++.
Copyright (C) 2006-2016 Carl Philipp Reh (carlphilippreh <at> gmail.com)

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


#include <sge/bvh/dummy_node.hpp>
#include <sge/bvh/object_impl.hpp>
#include <sge/bvh/tree_traits.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/text.hpp>
#include <fcppt/container/tree/depth.hpp>
#include <fcppt/io/cerr.hpp>
#include <fcppt/math/box/rect.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/generator/minstd_rand.hpp>
#include <fcppt/random/generator/seed_from_chrono.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <ostream>
#include <string>
#include <fcppt/config/external_end.hpp>


int
main(
	int argc,
	char *argv[])
try
{
	if(argc == 1)
	{
		std::cerr << "Usage: " << argv[0] << " <rectangle-count>\n";
		return EXIT_FAILURE;
	}

	unsigned const rectangle_count =
		fcppt::extract_from_string_exn<unsigned>(
			std::string(
				argv[1]));

	typedef
	fcppt::math::box::rect<float>
	bvh_box;

	typedef
	sge::bvh::tree_traits
	<
		sge::bvh::dummy_node,
		bvh_box,
		bvh_box
	>
	bvh_tree_traits;

	bvh_box::dim const total_bounding_box(
		1024.0f,
		1024.0f
	);

	typedef
	fcppt::random::generator::minstd_rand
	generator_type;

	generator_type generator(
		fcppt::random::generator::seed_from_chrono<generator_type::seed>());

	typedef
	fcppt::random::distribution::basic
	<
		fcppt::random::distribution::parameters::uniform_real
		<
			float
		>
	>
	real_distribution;

	typedef
	fcppt::random::variate
	<
		generator_type,
		real_distribution
	>
	real_variate;

	real_variate
		screen_size_rng(
			generator,
			real_distribution(
				real_distribution::param_type::min(
					total_bounding_box.h()/8.0f),
				real_distribution::param_type::sup(
					total_bounding_box.h() - total_bounding_box.h()/8.0f))),
		size_rng(
			generator,
			real_distribution(
				real_distribution::param_type::min(
						total_bounding_box.h()/16.0f),
				real_distribution::param_type::sup(
					total_bounding_box.h()/4.0f)));


	sge::bvh::object<bvh_tree_traits> bounding_hierarchy;

	bvh_tree_traits::leaf_sequence nodes;
	for(unsigned i = 0; i < rectangle_count; ++i)
	{
		bvh_box::dim const new_size(
			size_rng(),
			size_rng());

		nodes.push_back(
			bvh_box(
				bvh_box::vector(
					screen_size_rng(),
					screen_size_rng()) -
				new_size/2.0f,
				new_size));
	}

	typedef
	std::chrono::steady_clock
	clock_type;

	clock_type::time_point const before =
		clock_type::now();

	bounding_hierarchy.insert(
		nodes);

	std::cout
		<< "Construction time: "
		<<
			std::chrono::duration_cast<std::chrono::milliseconds>(
				clock_type::now() - before).count()
		<< "\n";

	std::cout
		<< "Tree depth: "
		<< fcppt::container::tree::depth(bounding_hierarchy.representation())
		<< "\n";
}
catch(
	fcppt::exception const &_error
)
{
	fcppt::io::cerr()
		<< _error.string()
		<< FCPPT_TEXT('\n');

	return EXIT_FAILURE;
}
catch(
	std::exception const &_error
)
{
	std::cerr
		<< _error.what()
		<< '\n';

	return EXIT_FAILURE;
}
