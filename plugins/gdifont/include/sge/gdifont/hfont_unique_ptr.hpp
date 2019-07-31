//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_GDIFONT_HFONT_UNIQUE_PTR_HPP_INCLUDED
#define SGE_GDIFONT_HFONT_UNIQUE_PTR_HPP_INCLUDED

#include <sge/gdifont/delete_object_deleter.hpp>
#include <sge/gdifont/include_windows.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace gdifont
{

typedef
fcppt::unique_ptr<
	std::remove_pointer<
		HFONT
	>::type,
	sge::gdifont::delete_object_deleter
>
hfont_unique_ptr;

}
}

#endif
