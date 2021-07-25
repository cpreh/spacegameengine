//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_BVH_CONSTRUCT_MEDIAN_CUT_HPP_INCLUDED
#define SGE_BVH_CONSTRUCT_MEDIAN_CUT_HPP_INCLUDED

#include <sge/bvh/bounding_box.hpp>
#include <sge/bvh/empty_node.hpp>
#include <sge/bvh/traits/box.hpp>
#include <sge/core/exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/size_type.hpp>
#include <fcppt/math/to_array.hpp>
#include <fcppt/math/box/center.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/range/algorithm/max_element.hpp>
#include <boost/range/algorithm/sort.hpp>
#include <algorithm>
#include <iterator>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace bvh
{
namespace detail
{

// TODO(philipp): This is a mess
class construct_median_cut_comparator
{
public:
	explicit
	construct_median_cut_comparator(
		fcppt::math::size_type const _axis)
	:
		axis_(
			_axis)
	{
	}

	template<typename LeafWrapper>
	bool
	operator()(
		LeafWrapper const &_left,
		LeafWrapper const &_right) const
	{
		using
		leaf
		=
		typename
		LeafWrapper::leaf;

		return
			fcppt::math::box::center(
				sge::bvh::traits::box<leaf>::extract_box(
					_left.value()
				)
			).get_unsafe(axis_)
			<
			fcppt::math::box::center(
				sge::bvh::traits::box<leaf>::extract_box(
					_right.value()
				)
			).get_unsafe(axis_);
	}

	[[nodiscard]]
	fcppt::math::size_type
	axis() const
	{
		return
			axis_;
	}
private:
	fcppt::math::size_type axis_;
};

}

template<typename Traits>
void
construct_median_cut(
	typename Traits::leaf_wrapper_sequence _leaves,
	typename Traits::tree_representation &_tree)
{
	if(
		!_tree.empty()
	)
	{
		throw
			sge::core::exception{
				FCPPT_TEXT("construct_median_cut: Tree not empty!")
			};
	}

	if(_leaves.size() <= 1U)
	{
		_tree.value(
			typename Traits::node_or_leaf_variant(
				_leaves));
		return;
	}

	typename Traits::box const bounding_box =
		sge::bvh::bounding_box<Traits>(
			_leaves);

	typename Traits::box::dim const bounding_box_size =
		bounding_box.size();

	_tree.value(
		typename Traits::node_or_leaf_variant(
			typename Traits::node_wrapper(
				typename Traits::node(
					bounding_box),
				bounding_box)));

	sge::bvh::detail::construct_median_cut_comparator comparator{
		[
			bounding_box_size
		]{
			auto const array(
				fcppt::math::to_array(
					bounding_box_size
				)
			);

			return
				static_cast<
					fcppt::math::size_type
				>(
					std::distance(
						array.begin(),
						boost::range::max_element(
							array
						)
					)
				);
		}()
	};

	std::nth_element(
		_leaves.begin(),
		std::next(
			_leaves.begin(),
			static_cast<typename Traits::leaf_wrapper_sequence::difference_type>(
				_leaves.size()/2U)),
		_leaves.end(),
		comparator);

	typename Traits::leaf_wrapper const &median(
		*std::next(
			_leaves.begin(),
			static_cast<typename Traits::leaf_wrapper_sequence::difference_type>(
				_leaves.size()/2U)));

	std::partition(
		_leaves.begin(),
		_leaves.end(),
		[
			median,
			&comparator
		](
			typename Traits::leaf_wrapper const &_value
		)
		{
			return
				comparator(
					_value,
					median
				);
		}
	);

	/*
	typename Traits::leaf_wrapper_sequence left_side,right_side;
	left_side.reserve(
		_leaves.size()/2U);
	right_side.reserve(
		_leaves.size()/2U);
	for(
		typename Traits::leaf_wrapper_sequence::iterator it =
			_leaves.begin();
		it != _leaves.end();
		++it)
		if(comparator((*it),median))
			left_side.push_back(
				*it);
		else
			right_side.push_back(
				*it);
				*/
	/*
	boost::range::sort(
		_leaves,
		sge::bvh::detail::construct_median_cut_comparator(
			static_cast<fcppt::math::size_type>(
				std::distance(
					bounding_box_size.begin(),
					boost::range::max_element(
						bounding_box_size)))));
	*/

	/*
	if(_leaves.size() == 2)
	{
		std::cout
			<<
				fcppt::math::box::center(
					sge::bvh::traits::box<typename Traits::leaf_wrapper::leaf>::extract_box(
						_leaves[0].value()))[comparator.axis()]
			<<
			", "
			<<
				fcppt::math::box::center(
					sge::bvh::traits::box<typename Traits::leaf_wrapper::leaf>::extract_box(
						_leaves[1].value()))[comparator.axis()]
			<<
			", median: "
			<<
				fcppt::math::box::center(
					sge::bvh::traits::box<typename Traits::leaf_wrapper::leaf>::extract_box(
						median.value()))[comparator.axis()]
			<<
			"\n";
	}
	*/
	/*
	std::cout << "input length: " << _leaves.size() << "\n";
	std::cout << "left side: " << left_side.size() << "\n";
	std::cout << "right side: " << right_side.size() << "\n";
	*/

	_tree.push_back(
		typename Traits::node_or_leaf_variant(
			sge::bvh::empty_node()));

	_tree.push_back(
		typename Traits::node_or_leaf_variant(
			sge::bvh::empty_node()));

	sge::bvh::construct_median_cut<Traits>(
		typename Traits::leaf_wrapper_sequence(
			_leaves.begin(),
			std::next(
				_leaves.begin(),
				static_cast<typename Traits::leaf_wrapper_sequence::difference_type>(
					_leaves.size()/2U))),
		_tree.front().get_unsafe().get()
	);

	sge::bvh::construct_median_cut<Traits>(
		typename Traits::leaf_wrapper_sequence(
			std::next(
				_leaves.begin(),
				static_cast<typename Traits::leaf_wrapper_sequence::difference_type>(
					_leaves.size()/2U)),
			_leaves.end()),
		*std::next(
			_tree.begin()));
}
}
}

#endif
