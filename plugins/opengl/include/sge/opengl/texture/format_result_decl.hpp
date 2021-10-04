//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_FORMAT_RESULT_DECL_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_FORMAT_RESULT_DECL_HPP_INCLUDED

#include <sge/opengl/texture/format_result_fwd.hpp>


namespace sge::opengl::texture
{

template<
	typename SGEFormat,
	typename GLFormat
>
class format_result
{
public:
	format_result(
		SGEFormat,
		GLFormat
	);

	[[nodiscard]]
	SGEFormat
	sge_format() const;

	[[nodiscard]]
	GLFormat
	gl_format() const;
private:
	SGEFormat sge_format_;

	GLFormat gl_format_;
};

}

#endif
