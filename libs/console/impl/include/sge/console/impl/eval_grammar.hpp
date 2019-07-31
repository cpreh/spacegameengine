//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CONSOLE_IMPL_EVAL_GRAMMAR_HPP_INCLUDED
#define SGE_CONSOLE_IMPL_EVAL_GRAMMAR_HPP_INCLUDED

#include <sge/console/arg_list.hpp>
#include <sge/console/impl/eval_grammar_fwd.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/string.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/parse/epsilon.hpp>
#include <fcppt/parse/grammar_decl.hpp>


namespace sge
{
namespace console
{
namespace impl
{

class eval_grammar final
:
public
	fcppt::parse::grammar<
		sge::console::arg_list,
		sge::font::char_type,
		fcppt::parse::epsilon
	>
{
	FCPPT_NONCOPYABLE(
		eval_grammar
	);
public:
	eval_grammar();

	~eval_grammar();
private:
	base_type<
		sge::font::string
	> word_;

	base_type<
		sge::font::string
	> quoted_string_;

	base_type<
		sge::font::string
	> argument_;

	base_type<
		sge::console::arg_list
	> start_;
};

}
}
}

#endif
