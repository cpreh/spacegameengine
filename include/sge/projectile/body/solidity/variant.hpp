#ifndef SGE_PROJECTILE_BODY_SOLIDITY_VARIANT_HPP_INCLUDED
#define SGE_PROJECTILE_BODY_SOLIDITY_VARIANT_HPP_INCLUDED

#include <sge/projectile/body/solidity/static.hpp>
#include <sge/projectile/body/solidity/solid.hpp>
#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <fcppt/variant/object.hpp>
#include <boost/mpl/vector/vector10.hpp>

namespace sge
{
namespace projectile
{
namespace body
{
namespace solidity
{
typedef
fcppt::variant::object
<
	boost::mpl::vector3
	<
		static_,
		solid,
		nonsolid
	>
>
variant;
}
}
}
}

#endif
