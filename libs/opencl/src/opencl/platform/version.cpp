//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#include <sge/opencl/platform/version.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/compiler.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/fusion/container/vector/vector10.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/spirit/include/qi_char.hpp>
#include <boost/spirit/include/qi_lit.hpp>
#include <boost/spirit/include/qi_operator.hpp>
#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/qi_uint.hpp>
#include <boost/spirit/include/support_standard.hpp>
#include <string>
#include <vector>
#include <fcppt/config/external_end.hpp>


// TODO(philipp): Initialize this directly
sge::opencl::platform::version::version(
	std::string const &_version_string
)
:
	major_(),
	minor_(),
	platform_specific_()
{
	// TODO(philipp): Use fcppt::parse

	namespace qi = boost::spirit::qi;

	std::string::const_iterator begin{
		_version_string.begin()
	};

	std::string::const_iterator end{
		_version_string.end()
	};

FCPPT_PP_PUSH_WARNING
#if defined(FCPPT_CONFIG_GNU_GCC_COMPILER)
FCPPT_PP_DISABLE_GCC_WARNING(-Wzero-as-null-pointer-constant)
#endif

	qi::uint_parser<version::unit> unit_parser;

	using
	output_type
	=
	boost::fusion::vector3<
		version::unit,
		version::unit,
		std::vector<char>
	>;

	output_type output;

	bool const res{
		qi::parse(
			begin,
			end,
			qi::lit("OpenCL ")
			>>
			unit_parser
			>>
			qi::lit(".")
			>>
			unit_parser
			>>
			qi::lit(" ")
			>>
			(*boost::spirit::standard::char_)
			,
			output
		)
	};

	major_ =
		boost::fusion::at_c<0>(
			output);

	minor_ =
		boost::fusion::at_c<1>(
			output);

	platform_specific_ =
		std::string(
			boost::fusion::at_c<2>(
				output).begin(),
			boost::fusion::at_c<2>(
				output).end());

	FCPPT_ASSERT_PRE(
		begin == end && res);

FCPPT_PP_POP_WARNING
}

sge::opencl::platform::version::unit
sge::opencl::platform::version::major_part() const
{
	return major_;
}

sge::opencl::platform::version::unit
sge::opencl::platform::version::minor_part() const
{
	return minor_;
}

std::string const &
sge::opencl::platform::version::platform_specific() const
{
	return platform_specific_;
}
