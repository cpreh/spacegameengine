//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_MUXING_STREAMBUF_HPP_INCLUDED
#define SGE_CONSOLE_MUXING_STREAMBUF_HPP_INCLUDED

#include <sge/console/muxing.hpp>
#include <sge/console/muxing_streambuf_fwd.hpp>
#include <sge/console/object_fwd.hpp>
#include <sge/console/detail/symbol.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <streambuf>
#include <string>
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
template<
	typename Char,
	typename Traits
>
class muxing_streambuf
:
	std::basic_streambuf<
		Char,
		Traits
	>
{
	FCPPT_NONCOPYABLE(
		muxing_streambuf
	);
public:
	typedef
	std::basic_streambuf<
		Char,
		Traits
	>
	streambuf_base;

	typedef
	typename
	streambuf_base::int_type
	int_type;

	SGE_CONSOLE_DETAIL_SYMBOL
	muxing_streambuf(
		std::basic_ostream<
			Char,
			Traits
		> &,
		sge::console::object &,
		sge::console::muxing
	);

	SGE_CONSOLE_DETAIL_SYMBOL
	~muxing_streambuf()
	override;
private:
	bool in_progress_;

	sge::console::object &object_;

	std::basic_ostream<
		Char,
		Traits
	> &stream_;

	fcppt::unique_ptr<
		std::basic_streambuf<
			Char,
			Traits
		>
	> old_streambuf_;

	sge::console::muxing const does_muxing_;

	std::basic_string<
		Char,
		Traits
	> buffer_;

	int_type
	overflow(
		int_type
	)
	override;
};

}
}

#endif
