//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_RAW_VALUE_HPP_INCLUDED
#define SGE_RENDERER_RAW_VALUE_HPP_INCLUDED


namespace sge
{
namespace renderer
{

/**
\brief The type of raw data

\ingroup sge_renderer

Buffer data can be accessed raw as if it was an array of bytes. This can be
useful if you want to bypass the type system so you can directly copy into or
read from a buffer.
*/
typedef unsigned char raw_value;

}
}

#endif
