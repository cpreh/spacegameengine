//          Copyright Carl Philipp Reh 2006 - 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)


#ifndef SGE_RENDERER_INDEX_CONST_PROXY_DECL_HPP_INCLUDED
#define SGE_RENDERER_INDEX_CONST_PROXY_DECL_HPP_INCLUDED

#include <sge/renderer/index/const_proxy_fwd.hpp>
#include <sge/renderer/index/const_tag.hpp>
#include <sge/renderer/index/format.hpp>
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
class const_proxy
{
public:
	static_assert(
		std::is_same<
			typename Format::constness,
			sge::renderer::index::const_tag
		>::value,
		"const_proxy can only use const formats"
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
	const_proxy(
		pointer
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
