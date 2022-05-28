/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:44:06 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:48:56 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

#include "IteratorTraits.hpp"

namespace ft
{
	template <class Iterator>
	class ReverseIterator
	{
	public:
		typedef typename Iterator::iterator_category	iterator_category;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::const_iterator		const_type;
		typedef Iterator								iterator_type;
		typedef ReverseIterator<iterator_type>			iterator;
		typedef ReverseIterator<const_type>				const_iterator;

	protected:
		iterator_type	_cur;

	public:
		//canonical form
		ReverseIterator() : _cur() {};
		explicit ReverseIterator(iterator_type iter) : _cur(iter) {};
		template <class Iter>
		ReverseIterator(const ReverseIterator<Iter>& iter) : _cur(iter.base()) {};
		~ReverseIterator() {};
		iterator_type base(void) const
		{
			return _cur;
		}

		//increment and decrement
		ReverseIterator& operator++()
		{
			--_cur;
			return *this;
		}
		ReverseIterator operator++(int)
		{
			ReverseIterator tmp = *this;
			--_cur;
			return tmp;
		}
		ReverseIterator& operator--()
		{
			++_cur;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator tmp = *this;
			++_cur;
			return tmp;
		}
		ReverseIterator operator+(difference_type n) const
		{
			return ReverseIterator(base() - n);
		}
		ReverseIterator operator-(difference_type n) const
		{
			return ReverseIterator(base() + n);
		}
		ReverseIterator& operator+=(difference_type n)
		{
			_cur -= n;
			return *this;
		}
		ReverseIterator& operator-=(difference_type n)
		{
			_cur += n;
			return *this;
		}

		//dereference operator
		reference operator[] (difference_type n) const
		{
			return (base()[n]);
		}
		reference operator*() const
		{
			return *(base());
		}
		pointer operator->() const
		{
			return &(operator*());
		}
	};

	//non-member functions
	//comparison by iterators
	template <class T>
	bool operator<(const ReverseIterator<T>& lhs, const ReverseIterator<T>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class T>
	bool operator>(const ReverseIterator<T>& lhs, const ReverseIterator<T>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class T>
	bool operator<=(const ReverseIterator<T>& lhs, const ReverseIterator<T>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class T>
	bool operator>=(const ReverseIterator<T>& lhs, const ReverseIterator<T>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class T>
	bool operator==(const ReverseIterator<T>& lhs, const ReverseIterator<T>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class T>
	bool operator!=(const ReverseIterator<T>& lhs, const ReverseIterator<T>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class T_lhs, class T_rhs>
	bool operator==(const ReverseIterator<T_lhs>& lhs, const ReverseIterator<T_rhs>& rhs)
	{
		return lhs.base() == rhs.base();
	}

	template <class T_lhs, class T_rhs>
	bool operator!=(const ReverseIterator<T_lhs>& lhs, const ReverseIterator<T_rhs>& rhs)
	{
		return lhs.base() != rhs.base();
	}

	template <class T_lhs, class T_rhs>
	bool operator<(const ReverseIterator<T_lhs>& lhs, const ReverseIterator<T_rhs>& rhs)
	{
		return lhs.base() > rhs.base();
	}

	template <class T_lhs, class T_rhs>
	bool operator>(const ReverseIterator<T_lhs>& lhs, const ReverseIterator<T_rhs>& rhs)
	{
		return lhs.base() < rhs.base();
	}

	template <class T_lhs, class T_rhs>
	bool operator<=(const ReverseIterator<T_lhs>& lhs, const ReverseIterator<T_rhs>& rhs)
	{
		return lhs.base() >= rhs.base();
	}

	template <class T_lhs, class T_rhs>
	bool operator>=(const ReverseIterator<T_lhs>& lhs, const ReverseIterator<T_rhs>& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	ReverseIterator<Iterator> operator+(typename Iterator::difference_type n, const ReverseIterator<Iterator>& iter)
	{
		return ReverseIterator<Iterator>(iter.base() - n);
	}

	template <class Iterator>
	ReverseIterator<Iterator> operator-(typename Iterator::difference_type n, const ReverseIterator<Iterator>& iter)
	{
		return ReverseIterator<Iterator>(iter.base() + n);
	}
}


#endif
