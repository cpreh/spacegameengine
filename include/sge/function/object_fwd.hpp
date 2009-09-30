
#ifndef SGE_FUNCTION_OBJECT_FWD_HPP
#define SGE_FUNCTION_OBJECT_FWD_HPP

namespace sge
{

namespace function
{

/**
 * @brief a fully std tr1 compliant function object class
 *
 * This class was introduced beause the gcc implementation had problems
 * with boost::phoenix.
 * To encounter this, sge::function::object is a wrapper around std::tr1::function
 *
 */
template< typename Singature >
struct object;

} // end namespace function

} // end namespace sge

#endif
