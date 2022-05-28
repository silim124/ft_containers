/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:44:00 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:49:00 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		public:
			typedef T1		first_type;
			typedef T2		second_type;
			first_type		first;
			second_type		second;

		// Constructor
		public:
			// default
			pair() : first(T1()), second(T2()) {}

			// copy
			template<class U, class V>
			pair(const pair<U, V> &p) : first(p.first), second(p.second) {}

			// initialization
			pair(const first_type &x, const second_type &y) : first(x), second(y) {}

			// Destructor
			~pair() {}

			// assignment operator
			pair	&operator=(const pair &p)
			{
				this->first = p.first;
				this->second = p.second;
				return (*this);
			}
	};

		// relational operators
		template <class T1, class T2>
		bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

		template <class T1, class T2>
		bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return !(lhs == rhs);
		}

		template <class T1, class T2>
		bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
		}

		template <class T1, class T2>
		bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return !(rhs < lhs);
		}

		template <class T1, class T2>
		bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return (rhs < lhs);
		}

		template <class T1, class T2>
		bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
		{
			return !(lhs < rhs);
		}

		// make pair
		template <class T1, class T2>
		pair<T1, T2> make_pair(T1 x, T2 y)
		{
			return (pair<T1, T2>(x, y));
		}
}

#endif
