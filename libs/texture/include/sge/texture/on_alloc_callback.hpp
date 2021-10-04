//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_TEXTURE_ON_ALLOC_CALLBACK_HPP_INCLUDED
#define SGE_TEXTURE_ON_ALLOC_CALLBACK_HPP_INCLUDED

#include <sge/texture/on_alloc_function.hpp>
#include <fcppt/function_impl.hpp>


namespace sge::texture
{

using
on_alloc_callback
=
fcppt::function<
	sge::texture::on_alloc_function
>;

}

#endif
