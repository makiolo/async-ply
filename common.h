// design-patterns-cpp14 by Ricardo Marmolejo Garc�a is licensed under a Creative Commons
// Reconocimiento 4.0 Internacional License.
// http://creativecommons.org/licenses/by/4.0/
//
#ifndef _PATTERNS_COMMON_
#define _PATTERNS_COMMON_

#include <functional>
#include <string>
#include <memory>
#include <unordered_map>
#include <exception>

#define DEFINE_HASH(__CLASS__)  \
	namespace std               \
	{                           \
	template <>                 \
	struct hash<__CLASS__>      \
	{                           \
	public:                     \
		size_t operator()() const { return std::hash<std::string>()(#__CLASS__); }                          \
	};                          \
	}

template <int...>
struct int_sequence
{
};

template <int N, int... Is>
struct make_int_sequence : make_int_sequence<N - 1, N - 1, Is...>
{
};

template <int... Is>
struct make_int_sequence<0, Is...> : int_sequence<Is...>
{
};

template <int>
struct placeholder_template
{
};

namespace std
{
template <int N>
struct is_placeholder<placeholder_template<N>> : integral_constant<int, N + 1>
{
};
}

template <int... Is>
struct seq
{
};

template <int N, int... Is>
struct gens : gens<N - 1, N - 1, Is...>
{
};

template <int... Is>
struct gens<0, Is...> : seq<Is...>
{
};

namespace dp14
{

template <typename T>
class hash
{
public:
	template <typename... Args>
	size_t operator()(Args&&... args) const
	{
		size_t h = 0;
		_hash_forwarding(h, std::forward<Args>(args)...);
		return h;
	}

protected:
	template <typename U>
	void _combine_hash(size_t& seed, U&& x) const
	{
		seed ^= std::hash<U>()(std::forward<U>(x)) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	template <typename U, typename... Args>
	void _hash_forwarding(size_t& h, U&& parm, Args&&... args) const
	{
		_combine_hash<U>(h, std::forward<U>(parm));
		_hash_forwarding(h, std::forward<Args>(args)...);
	}

	template <typename U>
	void _hash_forwarding(size_t& h, U&& parm) const
	{
		_combine_hash<U>(h, std::forward<U>(parm));
	}
};
}

#endif
