#ifndef __Utility_InlineFunctions_H__
#define __Utility_InlineFunctions_H__

#include <type_traits> //for std::underlying_type

#define ABS(a) (((a) > 0) ? (a) : (-(a)))
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define MAX3(a, b, c) (MAX2(MAX2((a), (b)), (c)))

template<typename E>
/*constexpr El239: - can be, but not in VS2012*/ auto enumValueToInt(E e) -> typename std::underlying_type<E>::type // Convert any enum class value to underlying int type
{
   return static_cast<typename std::underlying_type<E>::type>(e);
}

#endif //__Utility_InlineFunctions_H__