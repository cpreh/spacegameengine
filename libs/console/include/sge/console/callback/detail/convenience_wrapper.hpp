//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_CALLBACK_DETAIL_CONVENIENCE_WRAPPER_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_DETAIL_CONVENIENCE_WRAPPER_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/detail/conversion_visitor.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/function_impl.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_metal.hpp>
#include <fcppt/algorithm/loop_break_tuple.hpp>
#include <fcppt/algorithm/map_tuple.hpp>
#include <fcppt/container/array/from_range.hpp>
#include <fcppt/container/tuple/apply.hpp>
#include <fcppt/container/tuple/from_array.hpp>
#include <fcppt/metal/as_tuple.hpp>
#include <fcppt/metal/from_number.hpp>
#include <fcppt/metal/function_args.hpp>
#include <fcppt/metal/interval.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/optional/sequence.hpp>
#include <fcppt/config/external_begin.hpp>
#include <metal.hpp>
#include <array>
#include <cstddef>
#include <tuple>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
namespace callback
{
namespace detail
{

template<
	typename FunctionType
>
class convenience_wrapper
{
public:
	using
	function_type
	=
	FunctionType;

	template<
		typename Function
	>
	convenience_wrapper(
		Function &&_function,
		sge::font::string &&_short_description
	)
	:
		function_(
			std::forward<
				Function
			>(
				_function
			)
		),
		short_description_(
			std::move(
				_short_description
			)
		)
	{
	}

	void
	operator()(
		sge::console::arg_list const &_args,
		sge::console::object_ref const _console
	) const
	{
		using
		arg_types
		=
		fcppt::metal::function_args<
			function_type
		>;

		using
		arg_count
		=
		fcppt::metal::from_number<
			std::size_t,
			::metal::size<
				arg_types
			>
		>;

		using
		static_args
		=
		std::array<
			sge::font::string,
			arg_count::value
		>;

		fcppt::optional::maybe(
			fcppt::container::array::from_range<
				arg_count::value
			>(
				// TODO(philipp): Range from begin + 1 to end?
				_args
			),
			[
				&_console,
				this
			]{
				_console.get().emit_error(
					SGE_FONT_LIT("Given too few or too many arguments!")
				);

				_console.get().emit_error(
					this->short_description_
				);
			},
			[
				&_console,
				this
			](
				static_args const &_static_args
			)
			{
				using
				arguments
				=
				fcppt::metal::as_tuple<
					arg_types
				>;

				fcppt::optional::maybe_void(
					fcppt::optional::sequence<
						arguments
					>(
						fcppt::container::tuple::apply(
							sge::console::callback::detail::conversion_visitor<
								arg_types
							>{
								_console
							},
							fcppt::metal::as_tuple<
								fcppt::metal::interval<
									std::size_t,
									0U,
									arg_count::value
								>
							>{},
							fcppt::container::tuple::from_array(
								_static_args
							)
						)
					),
					[
						this
					](
						arguments &&_inner_args
					)
					{
						std::apply(
							this->function_,
							std::move(
								_inner_args
							)
						);
					}
				);
			}
		);
	}
private:
	fcppt::function<
		function_type
	> function_;

	sge::font::string short_description_;
};

}
}
}
}

#endif
