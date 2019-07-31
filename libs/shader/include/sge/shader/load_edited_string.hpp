//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_SHADER_LOAD_EDITED_STRING_HPP_INCLUDED
#define SGE_SHADER_LOAD_EDITED_STRING_HPP_INCLUDED

#include <sge/cg/program/source.hpp>
#include <sge/renderer/device/core_fwd.hpp>
#include <sge/renderer/vertex/declaration_fwd.hpp>
#include <sge/shader/detail/symbol.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace shader
{
SGE_SHADER_DETAIL_SYMBOL
sge::cg::program::source
load_edited_string(
	sge::renderer::device::core &,
	sge::renderer::vertex::declaration const &,
	std::istream &);
}
}

#endif

