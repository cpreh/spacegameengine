//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_PLUGIN_OBJECT_HPP_INCLUDED
#define SGE_PLUGIN_OBJECT_HPP_INCLUDED

#include <sge/plugin/loader_function.hpp>
#include <sge/plugin/object_fwd.hpp>
#include <sge/plugin/detail/instantiate/symbol.hpp>
#include <sge/plugin/library/object_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/shared_ptr_impl.hpp>


namespace sge
{
namespace plugin
{

template<
	typename Type
>
class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	typedef
	sge::plugin::loader_function<
		Type
	>
	loader_function;

	typedef
	fcppt::shared_ptr<
		sge::plugin::library::object
	>
	library_shared_ptr;

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	explicit
	object(
		library_shared_ptr const &
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	object(
		object &&
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	object &
	operator=(
		object &&
	);

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	~object();

	SGE_PLUGIN_DETAIL_INSTANTIATE_SYMBOL
	loader_function
	get() const;
private:
	library_shared_ptr lib_;

	loader_function loader_;
};

}
}

#endif
