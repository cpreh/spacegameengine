//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


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
