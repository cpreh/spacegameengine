//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONTEXT_ID_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_ID_HPP_INCLUDED

#include <sge/opengl/context/id_fwd.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

class id
{
public:
	typedef
	unsigned
	type;

	explicit
	id(
		type
	);

	type
	get() const;
private:
	type value_;
};

}
}
}

#endif
