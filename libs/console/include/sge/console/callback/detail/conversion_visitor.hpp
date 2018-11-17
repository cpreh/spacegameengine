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


#ifndef SGE_CONSOLE_CALLBACK_DETAIL_CONVERSION_VISITOR_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_DETAIL_CONVERSION_VISITOR_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/object.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/tag.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <type_traits>
#include <typeinfo>
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
	typename ParameterTypes
>
struct conversion_visitor
{
public:
	conversion_visitor(
		sge::console::object &_console,
		ParameterTypes &_parameters,
		sge::console::arg_list const &_args
	)
	:
		console_(
			_console
		),
		parameters_(
			_parameters
		),
		args_(
			_args
		)
	{
	}

	template<
		typename Index
	>
	void
	operator()(
		fcppt::tag<
			Index
		>
	) const
	{
		typedef
		std::remove_reference_t<
			typename
			boost::fusion::result_of::at_c<
				ParameterTypes,
				Index::value
			>::type
		>
		result_type;

		fcppt::optional::maybe(
			fcppt::extract_from_string<
				result_type
			>(
				this->args_.get()[
					Index::value
					+
					1
				]
			),
			[
				this
			]{
				this->console_.get().emit_error(
					SGE_FONT_LIT("Couldn't convert argument ")
					+
					fcppt::output_to_string<
						sge::font::string
					>(
						Index::value
					)
					+
					SGE_FONT_LIT(" to type ")
					+
					sge::font::from_fcppt_string(
						fcppt::from_std_string(
							fcppt::type_name_from_info(
								typeid(
									result_type
								)
							)
						)
					)
				);
			},
			[
				this
			](
				result_type const &_converted
			)
			{
				boost::fusion::at_c<
					Index::value
				>(
					this->parameters_.get()
				) =
					_converted;
			}
		);
	}
private:
	fcppt::reference<
		sge::console::object
	> console_;

	fcppt::reference<
		ParameterTypes
	> parameters_;

	fcppt::reference<
		sge::console::arg_list const
	> args_;
};

}
}
}
}

#endif
