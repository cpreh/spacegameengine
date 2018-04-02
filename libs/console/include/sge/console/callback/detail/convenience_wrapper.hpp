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


#ifndef SGE_CONSOLE_CALLBACK_DETAIL_CONVENIENCE_WRAPPER_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_DETAIL_CONVENIENCE_WRAPPER_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/console/callback/detail/conversion_visitor.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/algorithm/loop.hpp>
#include <fcppt/algorithm/loop_break_brigand.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/function_types/function_arity.hpp>
#include <boost/function_types/parameter_types.hpp>
#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/functional/invocation/invoke.hpp>
#include <boost/fusion/include/mpl.hpp>
#include <brigand/sequences/range.hpp>
#include <cstddef>
#include <functional>
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
	typedef
	FunctionType
	function_type;

	template<
		typename Function
	>
	convenience_wrapper(
		Function const &_function,
		sge::font::string const &_short_description
	)
	:
		function_(
			_function
		),
		short_description_(
			_short_description
		)
	{
	}

	void
	operator()(
		sge::console::arg_list const &_args,
		sge::console::object &_console
	) const
	{
		std::size_t const arity{
			boost::function_types::function_arity<
				function_type
			>::value
		};

		if(_args.size() - 1u != arity)
		{
			_console.emit_error(
				SGE_FONT_LIT("Given too few or too many arguments!"));
			_console.emit_error(
				short_description_);
			return;
		}

		// TODO: Fix this
		typedef
		boost::function_types::parameter_types<
			function_type
		>
		arguments;

		typedef
		typename
		boost::fusion::result_of::as_vector<
			arguments
		>::type
		argument_tuple;

		argument_tuple parameter_tuple;

		fcppt::algorithm::loop(
			brigand::range<
				console::arg_list::size_type,
				0,
				boost::function_types::function_arity<
					function_type
				>::value
			>{},
			sge::console::callback::detail::conversion_visitor<
				argument_tuple
			>(
				_console,
				parameter_tuple,
				_args
			)
		);

		boost::fusion::invoke(
			function_,
			parameter_tuple
		);
	}
private:
	std::function<
		function_type
	> function_;

	sge::font::string short_description_;
};

}
}
}
}

#endif
