//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_IS_FORMAT_HPP_INCLUDED
#define SGE_RENDERER_INDEX_IS_FORMAT_HPP_INCLUDED

#include <sge/renderer/index/format_fwd.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Weffc++)

template<
	typename Format
>
struct is_format
:
std::false_type
{
};

template<
	typename Index,
	typename Constness
>
struct is_format<
	sge::renderer::index::format<
		Index,
		Constness
	>
>
:
std::true_type
{
};

FCPPT_PP_POP_WARNING

}
}
}

#endif
