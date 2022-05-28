/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:43:54 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:49:07 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MapIterator_HPP
# define MapIterator_HPP
# include "Node.hpp"
# include "BidirectionalIterator.hpp"
# include <cstddef>

namespace ft
{
	template < class Node, class T, class Pointer = T*, class Reference = T&>
	class MapIterator : public BidirectionalIterator< Node, Node*, Node& >
	{
		public:
			typedef MapIterator<Node, T>						iterator;
			typedef MapIterator<Node, const T>					const_iterator;
			typedef	BidirectionalIterator<Node, Node*, Node&> 	bidirectional_iterator;
			typedef ptrdiff_t									difference_type;
			typedef T*											pointer;
			typedef T&											reference;

		public:
			MapIterator() : bidirectional_iterator() {}

			MapIterator(Node *ptr) : bidirectional_iterator(ptr) {}

			~MapIterator() {}

			MapIterator(MapIterator const &src) { *this = src; }

			MapIterator	&operator=(MapIterator const &src)
			{
				this->_ptr = src._ptr;
				return (*this);
			}

			reference	operator*() const
			{
				return (this->_ptr->data);
			}

			pointer		operator->() const
			{
				return &(this->_ptr->data);
			}

			MapIterator	&operator++()
			{
				this->_ptr = this->_ptr->next();
				return (*this);
			}

			MapIterator	operator++(int)
			{
				MapIterator	it = *this;

				this->_ptr = this->_ptr->next();
				return (it);
			}

			MapIterator	&operator--()
			{
				this->_ptr = this->_ptr->prev();
				return (*this);
			}

			MapIterator	operator--(int)
			{
				MapIterator	it = *this;

				this->_ptr = this->_ptr->prev();
				return (it);
			}

			operator	const_iterator() const
			{
				return (const_iterator(this->_ptr));
			}
	};
}

#endif
