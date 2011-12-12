#ifndef SGE_CONSOLE_MUXING_STREAMBUF_DECL_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_DECL_HPP_INCLUDED

#include <sge/console/muxing.hpp>
#include <sge/console/symbol.hpp>
#include <sge/console/muxing_streambuf_fwd.hpp>
#include <sge/console/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <streambuf>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace console
{
/**
\brief Multiplex the output of an ostream to the console and to the original target
\tparam Char The character type
\tparam Traits The according char traits

There are situations where you want to know the output of an ostream (for
example: std::cout, fcppt::io::cout, std::cerr and so on), but do not have a
terminal window to look at (since you're running in full-screen mode, for example).

A console (an sge::console::object, to be precise), might be present, however.
So it would be great if you could redirect the output of the given ostream to
the console. This is what the muxing_streambuf does.
*/
template<typename Char,typename Traits>
class muxing_streambuf
:
		std::basic_streambuf<Char,Traits>
{
FCPPT_NONCOPYABLE(
	muxing_streambuf);
public:
	typedef
	std::basic_streambuf<Char,Traits>
	streambuf_base;

	// This is just here to help MSVC++ resolve the int_type (crappy
	// compiler)
	typedef typename
	streambuf_base::int_type
	int_type;

	SGE_CONSOLE_SYMBOL explicit
	muxing_streambuf(
		std::basic_ostream<Char,Traits> &,
		sge::console::object &,
		console::muxing::type);

	SGE_CONSOLE_SYMBOL ~muxing_streambuf();
private:
	bool in_progress_;
	sge::console::object &object_;
	std::basic_ostream<Char,Traits> &stream_;
	std::basic_streambuf<Char,Traits> *old_streambuf_;
	console::muxing::type does_muxing_;
	std::basic_string<Char,Traits> buffer_;

	int_type
	overflow(
		int_type);

	static fcppt::string
	from_string(
		std::string const &);

	static fcppt::string
	from_string(
		std::wstring const &);
};
}
}

#endif
