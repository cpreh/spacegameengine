//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_TEXTURE_HOLDER_HPP_INCLUDED
#define SGE_OPENGL_TEXTURE_HOLDER_HPP_INCLUDED

#include <sge/opengl/texture/id.hpp>
#include <fcppt/noncopyable.hpp>


namespace sge
{
namespace opengl
{
namespace texture
{

class holder
{
	FCPPT_NONCOPYABLE(
		holder
	);
public:
	holder();

	~holder();

	sge::opengl::texture::id
	id() const;
private:
	sge::opengl::texture::id const id_;
};

}
}
}

#endif
