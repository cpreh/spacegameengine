//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_PROXY_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_PROXY_DECL_HPP_INCLUDED

#include <sge/renderer/index/format.hpp>
#include <sge/renderer/index/nonconst_tag.hpp>
#include <sge/renderer/index/proxy_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sge
{
namespace renderer
{
namespace index
{

template<
	typename Format
>
class proxy
{
public:
	static_assert(
		std::is_same<
			typename Format::constness,
			sge::renderer::index::nonconst_tag
		>::value,
		"proxy can only use nonconst formats"
	);

	typedef
	typename
	Format::index_type
	value_type;

	typedef
	typename
	Format::pointer
	pointer;

	explicit
	proxy(
		pointer
	);

	void
	set(
		value_type
	);

	value_type
	get() const;
private:
	pointer data_;
};

}
}
}

#endif
