//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_OPENGL_CONTEXT_OBJECT_HPP_INCLUDED
#define SGE_OPENGL_CONTEXT_OBJECT_HPP_INCLUDED

#include <sge/opengl/context/base_fwd.hpp>
#include <sge/opengl/context/base_unique_ptr.hpp>
#include <sge/opengl/context/id_fwd.hpp>
#include <sge/opengl/context/object_fwd.hpp>
#include <sge/opengl/context/optional_base_ref_fwd.hpp>
#include <sge/opengl/info/context_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/container/index_map_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


namespace sge
{
namespace opengl
{
namespace context
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	explicit
	object(
		sge::opengl::info::context const &
	);

	~object();

	sge::opengl::context::optional_base_ref
	get(
		sge::opengl::context::id
	);

	sge::opengl::context::base &
	insert(
		sge::opengl::context::id,
		sge::opengl::context::base_unique_ptr &&
	);

	sge::opengl::info::context const &
	info() const;
private:
	sge::opengl::info::context const &info_;

	typedef
	fcppt::optional::object<
		sge::opengl::context::base_unique_ptr
	>
	optional_base_unique_ptr;

	typedef
	fcppt::container::index_map<
		optional_base_unique_ptr
	>
	container;

	container elements_;
};

}
}
}

#endif
