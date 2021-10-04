//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_CALLBACK_DETAIL_CONVERSION_VISITOR_HPP_INCLUDED
#define SGE_CONSOLE_CALLBACK_DETAIL_CONVERSION_VISITOR_HPP_INCLUDED

#include <sge/console/object.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/string.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/type_name_from_info.hpp>
#include <fcppt/mpl/size_type.hpp>
#include <fcppt/mpl/list/at.hpp>
#include <fcppt/optional/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cstddef>
#include <type_traits>
#include <typeinfo>
#include <fcppt/config/external_end.hpp>


namespace sge::console::callback::detail
{

template<
	typename ParameterTypes
>
struct conversion_visitor
{
public:
	explicit
	conversion_visitor(
		fcppt::reference<
			sge::console::object
		> const _console
	)
	:
		console_{
			_console
		}
	{
	}

	template<
		std::size_t Index
	>
	fcppt::optional::object<
		std::remove_cvref_t<
			fcppt::mpl::list::at<
				ParameterTypes,
				fcppt::mpl::size_type<
					Index
				>
			>
		>
	>
	operator()(
		std::integral_constant<
			std::size_t,
			Index
		>,
		sge::font::string const &_value
	) const
	{
		using
		result_type
		=
		std::remove_cvref_t<
			fcppt::mpl::list::at<
				ParameterTypes,
				fcppt::mpl::size_type<
					Index
				>
			>
		>;

		fcppt::optional::object<
			result_type
		> result{
			fcppt::extract_from_string<
				result_type
			>(
				_value
			)
		};

		if(
			!result.has_value()
		)
		{
			this->console_.get().emit_error(
				SGE_FONT_LIT("Couldn't convert argument ")
				+
				fcppt::output_to_string<
					sge::font::string
				>(
					Index
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
		}

		return
			result;
	}
private:
	fcppt::reference<
		sge::console::object
	> console_;
};

}

#endif
