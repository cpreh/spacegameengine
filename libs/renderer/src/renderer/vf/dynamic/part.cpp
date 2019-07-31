//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/renderer/exception.hpp>
#include <sge/renderer/vf/dynamic/element_list.hpp>
#include <sge/renderer/vf/dynamic/offset_list.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/ordered_element_list.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/stride.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map.hpp>


sge::renderer::vf::dynamic::part::part(
	sge::renderer::vf::dynamic::element_list const &_elements,
	sge::renderer::vf::dynamic::offset_list const &_offsets
)
:
	elements_(
		[
			&_elements,
			&_offsets
		]{
			if(
				_elements.size()
				+
				1u
				!=
				_offsets.size()
			)
				throw
					sge::renderer::exception{
						FCPPT_TEXT("dynamic::format: Invalid sizes of vectors!")
					};

			return
				fcppt::algorithm::map<
					sge::renderer::vf::dynamic::ordered_element_list
				>(
					fcppt::make_int_range_count(
						_elements.size()
					),
					[
						&_elements,
						&_offsets
					](
						sge::renderer::vf::dynamic::element_list::size_type const _index
					)
					{
						return
							sge::renderer::vf::dynamic::ordered_element(
								_elements[
									_index
								],
								_offsets[
									_index
								]
							);
					}
				);
		}()
	),
	stride_(
		sge::renderer::vf::dynamic::stride(
			_offsets.back().get()
		)
	)
{
}

sge::renderer::vf::dynamic::ordered_element_list const &
sge::renderer::vf::dynamic::part::elements() const
{
	return
		elements_;
}

sge::renderer::vf::dynamic::stride
sge::renderer::vf::dynamic::part::stride() const
{
	return
		stride_;
}
