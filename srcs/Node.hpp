/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:43:58 by silim             #+#    #+#             */
/*   Updated: 2022/05/28 15:49:04 by silim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

namespace ft
{
	template <class T>
	class Node
	{
		public:
			Node		*parent;
			Node		*left;
			Node		*right;
			Node		*begin;
			Node		*end;
			T			data;
			int			height;

			Node()
				: parent(0), left(0), right(0), begin(0), end(0), data(T()), height(1) {}

			Node(T const &data)
				: parent(0), left(0), right(0), begin(0), end(0), data(data), height(1) {}

			~Node() {}

			Node(Node const &other)
			{
				*this = other;
			}

			Node	&operator=(Node const &other)
			{
				this->parent = other.parent;
				this->left = other.left;
				this->right = other.right;
				this->begin = other.begin;
				this->end = other.end;
				this->data = other.data;
				this->height = other.height;
				return (*this);
			}

			Node	*next() const
			{
				Node	*node= const_cast<Node*>(this);

				if (this->right || this == this->begin)
				{
					if (this == this->begin)
					{
						node= this->parent;
						if (!node)
							return (this->end);
					}
					else
						node= this->right;
					while (node->left)
						node= node->left;
				}
				else
				{
					while (node->parent && node->parent->right == node)
						node= node->parent;
					if (node->parent)
						node= node->parent;
					else
						node= node->end;
				}
				return (node);
			}

			Node	*prev() const
			{
				Node	*node= const_cast<Node*>(this);

				if (this->left || this == this->end)
				{
					if (this == this->end)
					{
						node= this->parent;
						if (!node)
							return (this->begin);
					}
					else
						node= this->left;
					while (node->right)
						node= node->right;
				}
				else
				{
					while (node->parent && node->parent->left == node)
						node= node->parent;
					if (node->parent)
						node= node->parent;
					else
						node= node->begin;
				}
				return (node);
			}

			int		get_height(Node *cur)
			{
				if (!cur)
					return (0);
				return (cur->height);
			}

			int		get_max(int a, int b)
			{
				return ((a > b) ? a : b);
			}

			void	update_height()
			{
				this->height = 1 + get_max(get_height(this->left), get_height(this->right));
			}

			int		get_balance()
			{
				return (get_height(this->left) - get_height(this->right));
			}

			void	rotate_right()
			{
				Node		*left = this->left;
				Node		*left_right = this->left->right;

				left->right = this;
				this->left = left_right;
				if (left_right)
					left_right->parent = this;
				left->parent = this->parent;
				this->parent = left;
				if (left->parent)
				{
					if (left->parent->left == this)
						left->parent->left = left;
					else
						left->parent->right = left;
				}
				this->update_height();
				left->update_height();
			}

			void	rotate_left()
			{
				Node		*rightNode = this->right;
				Node		*rightleft = this->right->left;

				rightNode->left = this;
				this->right = rightleft;
				if (rightleft)
					rightleft->parent = this;
				rightNode->parent = this->parent;
				this->parent = rightNode;
				if (rightNode->parent)
				{
					if (rightNode->parent->left == this)
						rightNode->parent->left = rightNode;
					else
						rightNode->parent->right = rightNode;
				}
				this->update_height();
				rightNode->update_height();
			}

			void	update_sentinel(Node *begin, Node *end)
			{
				if (this->left)
					this->left->update_sentinel(begin, end);
				if (this->right)
					this->right->update_sentinel(begin, end);
				this->begin = begin;
				this->end = end;
			}
	};
}

#endif
