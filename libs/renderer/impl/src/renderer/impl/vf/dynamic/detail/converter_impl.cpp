//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/image/color/format.hpp>
#include <sge/renderer/raw_pointer.hpp>
#include <sge/renderer/impl/vf/dynamic/element_converter.hpp>
#include <sge/renderer/impl/vf/dynamic/lock_interval.hpp>
#include <sge/renderer/impl/vf/dynamic/unlock.hpp>
#include <sge/renderer/impl/vf/dynamic/detail/converter_impl.hpp>
#include <sge/renderer/vertex/first.hpp>
#include <sge/renderer/vf/dynamic/color.hpp>
#include <sge/renderer/vf/dynamic/color_format_vector.hpp>
#include <sge/renderer/vf/dynamic/extra.hpp>
#include <sge/renderer/vf/dynamic/matching_color_format.hpp>
#include <sge/renderer/vf/dynamic/normal_fwd.hpp>
#include <sge/renderer/vf/dynamic/ordered_element.hpp>
#include <sge/renderer/vf/dynamic/part.hpp>
#include <sge/renderer/vf/dynamic/pos_fwd.hpp>
#include <sge/renderer/vf/dynamic/texpos_fwd.hpp>
#include <sge/renderer/vf/dynamic/vector_fwd.hpp>
#include <sge/renderer/vf/dynamic/detail/lock_interval_set.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/variant/match.hpp>


sge::renderer::vf::dynamic::detail::converter_impl::converter_impl(
	sge::renderer::vf::dynamic::part const &_part,
	sge::renderer::vf::dynamic::color_format_vector const &_accepted_formats
)
:
	element_converters_(
		fcppt::algorithm::map_optional<
			element_converter_vector
		>(
			_part.elements(),
			[
				&_accepted_formats,
				stride =
					_part.stride()
			](
				sge::renderer::vf::dynamic::ordered_element const &_element
			)
			{
				using
				optional_result
				=
				fcppt::optional::object<
					sge::renderer::impl::vf::dynamic::element_converter
				>;

				auto const convert_color(
					[
						stride,
						&_accepted_formats,
						offset = _element.offset()
					](
						sge::renderer::vf::dynamic::color const &_color
					)
					{
						sge::image::color::format const format(
							_color.color_format()
						);

						return
							sge::renderer::impl::vf::dynamic::element_converter{
								sge::renderer::impl::vf::dynamic::element_converter::original_format{
									format
								},
								sge::renderer::impl::vf::dynamic::element_converter::backend_format{
									sge::renderer::vf::dynamic::matching_color_format(
										format,
										_accepted_formats
									)
								},
								stride,
								offset
							};
					}
				);


				return
					fcppt::variant::match(
						_element.element().info(),
						[](
							sge::renderer::vf::dynamic::pos const &
						)
						{
							return
								optional_result{};
						},
						[](
							sge::renderer::vf::dynamic::normal const &
						)
						{
							return
								optional_result{};
						},
						[
							&convert_color
						](
							sge::renderer::vf::dynamic::color const &_color
						)
						{
							return
								optional_result{
									convert_color(
										_color
									)
								};
						},
						[](
							sge::renderer::vf::dynamic::texpos const &
						)
						{
							return
								optional_result{};
						},
						[
							&convert_color
						](
							sge::renderer::vf::dynamic::extra const &_extra
						)
						{
							return
								fcppt::variant::match(
									_extra.type(),
									[](
										sge::renderer::vf::dynamic::vector const &
									)
									{
										return
											optional_result{};
									},
									[
										&convert_color
									](
										sge::renderer::vf::dynamic::color const &_color
									)
									{
										return
											optional_result{
												convert_color(
													_color
												)
											};
									}
								);
						}
					);
			}
		)
	)
{
}

sge::renderer::vf::dynamic::detail::converter_impl::~converter_impl()
= default;

void
sge::renderer::vf::dynamic::detail::converter_impl::convert_lock(
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	sge::renderer::vf::dynamic::detail::lock_interval_set const &_intervals,
	sge::renderer::impl::vf::dynamic::lock_interval const &_current_lock
)
{
	for(
		sge::renderer::impl::vf::dynamic::lock_interval const &interval
		:
		(
			_intervals
			&
			_current_lock
		)
	)
	{
		this->do_convert(
			_data,
			_pos,
			interval,
			sge::renderer::impl::vf::dynamic::unlock{
				false
			}
		);
	}
}

void
sge::renderer::vf::dynamic::detail::converter_impl::convert_unlock(
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	sge::renderer::impl::vf::dynamic::lock_interval const &_current_lock
)
{
	this->do_convert(
		_data,
		_pos,
		_current_lock,
		sge::renderer::impl::vf::dynamic::unlock{
			true
		}
	);
}

void
sge::renderer::vf::dynamic::detail::converter_impl::do_convert(
	sge::renderer::raw_pointer const _data,
	sge::renderer::vertex::first const _pos,
	sge::renderer::impl::vf::dynamic::lock_interval const &_interval,
	sge::renderer::impl::vf::dynamic::unlock const _unlock
)
{
	for(
		sge::renderer::impl::vf::dynamic::element_converter const &conv
		:
		element_converters_
	)
	{
		conv.convert(
			_interval,
			_data,
			_pos,
			_unlock
		);
	}
}
