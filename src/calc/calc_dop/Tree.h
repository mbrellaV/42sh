#ifndef TREE_H
#define TREE_H

#include "common.h"
#include "libft.h"

typedef struct					s_calc_tree_node
{
	int							isChar;
	t_calc_data					*data;
	struct s_calc_tree_node 	*parent;
	struct s_calc_tree_node 	*left;
	struct s_calc_tree_node 	*right;
}								t_calc_tree_node;

typedef struct					s_calc_tree_root
{
	t_calc_tree_node			*root;
}								t_calc_tree_root;

t_calc_tree_root				*make_root_node();
t_calc_tree_node*				make_tree_node();
t_calc_tree_node*				make_child(t_calc_tree_node *parent_node, t_calc_data *datum, int left);
void							make_left_child(t_calc_tree_node *par_node, t_calc_data *datum);
void							make_right_child(t_calc_tree_node *par_node, t_calc_data *datum);
void							traversal(t_calc_tree_root *root, int mode);
void							preorder_traversal(t_calc_tree_node *tNode);
void							inorder_traversal(t_calc_tree_node *tNode);
void							postorder_traversal(t_calc_tree_node *tNode);
void							remove_all_tree_nodes(t_calc_tree_root* root);
void							remove_tree_node(t_calc_tree_node *tNode);

#endif // TREE_H_INCLUDED
