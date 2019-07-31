//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_CG_PROGRAM_COMPILE_OPTIONS_HPP_INCLUDED
#define SGE_CG_PROGRAM_COMPILE_OPTIONS_HPP_INCLUDED

#include <sge/cg/char_type.hpp>
#include <sge/cg/string.hpp>
#include <sge/cg/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace cg
{
namespace program
{

class compile_options
{
public:
	typedef
	std::vector<
		sge::cg::string
	>
	string_sequence;

	typedef
	std::vector<
		sge::cg::char_type const *
	>
	pointer_sequence;

	SGE_CG_DETAIL_SYMBOL
	compile_options();

	SGE_CG_DETAIL_SYMBOL
	explicit
	compile_options(
		sge::cg::char_type const **
	);

	SGE_CG_DETAIL_SYMBOL
	explicit
	compile_options(
		string_sequence
	);

	SGE_CG_DETAIL_SYMBOL
	pointer_sequence
	pointers() const;

	SGE_CG_DETAIL_SYMBOL
	string_sequence const &
	value() const;
private:
	string_sequence value_;
};

}
}
}

#endif
