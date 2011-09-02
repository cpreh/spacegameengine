#include <sge/opencl/version.hpp>
#include <fcppt/assert/pre.hpp>
// FIXME: I couldn't quite figure out which headers are needed here
// (apart from the obvious ones)
#include <boost/spirit/include/qi.hpp>
// Do we need to include at_c explicitly?
#include <boost/fusion/container/vector/vector10.hpp>
#include <vector>

sge::opencl::version::version(
	std::string const &_version_string)
{
  namespace qi = boost::spirit::qi;

  std::string::const_iterator
    begin =
     	_version_string.begin(),
    end =
      _version_string.end();

	qi::uint_parser<version::unit> unit_parser;

  typedef
  boost::fusion::vector3
  <
    version::unit,
    version::unit,
    std::vector<char>
  >
  output_type;

  output_type output;

  bool res =
    qi::parse(
      begin,
      end,
      qi::lit("OpenCL ") >> unit_parser >> qi::lit(".") >> unit_parser >> qi::lit(" ") >> (*boost::spirit::standard::char_),
      output);

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
}

sge::opencl::version::unit
sge::opencl::version::major_part() const
{
	return major_;
}

sge::opencl::version::unit
sge::opencl::version::minor_part() const
{
	return minor_;
}

std::string const &
sge::opencl::version::platform_specific() const
{
	return platform_specific_;
}
