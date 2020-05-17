#include "Tree.h"

t_calc_tree_root		*make_t_calc_tree_root_node()
{
	t_calc_tree_root	*tmp;
	if (!(tmp = (t_calc_tree_root*)ft_memalloc(sizeof(t_calc_tree_root))))
		return (NULL);
	return (tmp);
}

t_calc_tree_node		*make_tree_node()
{
	t_calc_tree_node* tmp;
	if (!(tmp = (t_calc_tree_node*)ft_memalloc(sizeof(t_calc_tree_node))))
		return (NULL);
	return (tmp);
}

/** \brief
 *
 * \param parent_node : parent node
 * \param datum : input data1
 * \param isChar : input data2
 * \return self node or new child node
 *
 */
t_calc_tree_node			*make_child(t_calc_tree_node *parent_node, t_calc_data *datum, int left)
{
	if(!parent_node)
	{
		parent_node = make_tree_node();
		parent_node->data = datum;
		return (parent_node);
	}
	if(left == 1)
	{
		if(parent_node->right)
		{
			make_left_child(parent_node, datum);
		}
		else
		{
			make_right_child(parent_node, datum);
		}
		return parent_node;
	}
	else
	{
		make_right_child(parent_node, datum);
		return (parent_node->right);
	}
}

void		make_left_child(t_calc_tree_node *pare_node, t_calc_data *datum)
{
	t_calc_tree_node*		tmp;

	tmp = make_tree_node();
	if(!tmp)
		return;
	tmp->data = datum;
	pare_node->left = tmp;
	tmp->parent = pare_node;
}

void		make_right_child(t_calc_tree_node *pare_node, t_calc_data *datum)
{
	t_calc_tree_node*		tmp ;

	tmp = make_tree_node();
	if(!tmp)
		return ;
	tmp->data = datum;
	pare_node->right = tmp;
	tmp->parent = pare_node;
}

void		print_data(t_calc_data *datum)
{
	printf("\n1: %d\n", datum->type);
	printf("2: %lld\n", datum->num);
	printf("3: %s\n", datum->var);
}

void traversal(t_calc_tree_root *t_calc_tree_root, int mode)
{
	t_calc_tree_node	*tmp;
	tmp = t_calc_tree_root->root;
	preorder_traversal(tmp);
}

void				preorder_traversal(t_calc_tree_node *tNode)
{
	if(!tNode)	return;
	print_data(tNode->data);
	preorder_traversal(tNode->left);
	preorder_traversal(tNode->right);
}

void				inorder_traversal(t_calc_tree_node *tNode)
{
	if(!tNode)	return;
	inorder_traversal(tNode->left);
	print_data(tNode->data);
	inorder_traversal(tNode->right);
}

void				postorder_traversal(t_calc_tree_node *tNode)
{
	if (!tNode)
		return ;
	postorder_traversal(tNode->left);
	postorder_traversal(tNode->right);
	print_data(tNode->data);
}

void				remove_tree_node(t_calc_tree_node *tNode)
{
	if(!tNode)
		return;
	remove_tree_node(tNode->left);
	remove_tree_node(tNode->right);
	free(tNode);
}

void				remove_all_tree_nodes(t_calc_tree_root* t_calc_tree_root)
{
	remove_tree_node(t_calc_tree_root->root);
}