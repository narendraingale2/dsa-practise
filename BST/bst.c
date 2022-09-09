#include<stdio.h>
#include<stdlib.h>
#include"bst.h"

bst_t* create_bst(void)
{
    bst_t* p_bst;
    p_bst = (bst_t*)malloc(sizeof(bst_t));
    if(p_bst == NULL)
    {
        fprintf(stderr, "malloc:fatal:out of virtual memmor \n");
        exit(EXIT_FAILURE);
    }
    p_bst->nr_nodes = 0;
    p_bst->p_root_node = NULL; 

}

status_t bst_insert(bst_t* p_bst, data_t new_element)
{
    bst_node_t* p_run = NULL;
    bst_node_t* p_new_node = NULL;

    
    p_run = p_bst -> p_root_node;
    p_new_node = get_bst_node(new_element);
    if(p_run == NULL)
    {
        p_bst ->p_root_node = p_new_node;
        p_bst -> nr_nodes += 1;
        return(SUCCESS);
    }
    while (1)
    {
       if(new_element <= p_run ->data)
       {
            if(p_run -> left == NULL)
            {
                p_run->left = p_new_node;
                p_new_node -> parent = p_run;
                p_bst -> nr_nodes += 1;
                return(SUCCESS);
            }
            else
            {
                p_run = p_run -> left;
            }
        
       } 
       else
       {
            if(p_run -> right == NULL)
            {
                p_run -> right = p_new_node;
                p_new_node -> parent = p_run;
                p_bst-> nr_nodes += 1;
                return(SUCCESS);
            }
            else
                p_run = p_run -> right;
       }
    }
}


status_t bst_remove(bst_t* p_bst, data_t r_data)
{
    bst_node_t* p_delete_node = NULL;
    bst_node_t* w = NULL;


    p_delete_node = search_node(p_bst,r_data);

    if(p_delete_node == NULL)
        return(TREE_DATA_NOT_FOUND);
    

    if(p_delete_node->left == NULL)
    {
        if(p_delete_node ->parent == NULL)
            p_bst->p_root_node = p_delete_node->right;
        
        if(p_delete_node->parent->left == p_delete_node)
            p_delete_node->parent->left = p_delete_node -> right;
        else
            p_delete_node->parent->right = p_delete_node -> right;
        
        if(p_delete_node ->right != NULL)
            p_delete_node -> right -> parent = p_delete_node->parent;

    }
    else if(p_delete_node -> right == NULL)
    {
        if(p_delete_node -> parent == NULL)
            p_bst->p_root_node = p_delete_node->left;
        
        if(p_delete_node->parent->left == p_delete_node)
            p_delete_node->parent->left = p_delete_node -> left;
        else
            p_delete_node->parent->right = p_delete_node -> left;
        
        if(p_delete_node ->left != NULL)
            p_delete_node -> left -> parent = p_delete_node->parent;
    }
    else
    {
        w = p_delete_node -> right;
        while (w -> left != NULL)
           w = w->left; 
        
        if(w != p_delete_node -> right)
        {
            w->parent->left = w->right;
            if(w->right != NULL)
                w->right->parent = w->parent;
            
            w->right = p_delete_node -> right;
            w->right->parent = w;
        }
        if(p_delete_node ->parent == NULL)
            p_bst->p_root_node = w;

        if(p_delete_node == p_delete_node ->parent->left)
            p_delete_node->parent->left = w;
        else
            p_delete_node->parent->right = w;
        
        w->parent = p_delete_node -> parent;
        w->left = p_delete_node -> left;
        w->left->parent = w;
    }

    p_bst->nr_nodes -= 1;
    free(p_delete_node);
    p_delete_node = NULL;

    return(SUCCESS);
        
}

status_t bst_search(bst_t* p_bst, data_t searh_data)
{
    return(search_node(p_bst,searh_data) != NULL);
}

status_t bst_is_empty(bst_t* p_bst)
{
    return(p_bst -> p_root_node == NULL);
}

data_t bst_max(bst_t* p_bst)
{
    bst_node_t* p_run = NULL;
    for(p_run = p_bst ->p_root_node; p_run->right != NULL; p_run = p_run->right);

    return(p_run->data);
}

data_t bst_min(bst_t* p_bst)
{
    bst_node_t* p_run = NULL;
    for(p_run = p_bst ->p_root_node; p_run->left != NULL; p_run = p_run->left);

    return(p_run->data);
}
unsigned long long int bst_get_nr_elements(bst_t* p_bst)
{
    return(p_bst->nr_nodes);
}

status_t destroy_bst(bst_t** p_bst)
{
    destroy_node((*p_bst)->p_root_node);
    free(*p_bst);
    p_bst = NULL;
}

/* in/pre/post order walks */
void preorder_r(bst_t* p_bst)
{
    puts("Preorder Walk ->");
    preorder_node(p_bst->p_root_node);
}

void postorder_r(bst_t* p_bst)
{
    puts("Postorder Walk ->");
    postorder_node(p_bst->p_root_node);
}

void inorder_r(bst_t* p_bst)
{
    puts("inorder Walk ->");
    inorder_node(p_bst->p_root_node);
}

bst_node_t* get_bst_node(data_t data)
{
    bst_node_t* p_new_node = NULL;
    p_new_node = (bst_node_t*)malloc(sizeof(bst_node_t));
    p_new_node->data = data;
    p_new_node->left = NULL;
    p_new_node->right = NULL;
    p_new_node->parent = NULL;
}


bst_node_t* search_node(bst_t* p_bst, data_t searh_data)
{
    bst_node_t* p_run = NULL;

    p_run = p_bst->p_root_node;

    while (p_run != NULL)
    {
        if(p_run -> data == searh_data)
            return(p_run);

        if(searh_data <= p_run)
            p_run = p_run -> left;
        else
            p_run = p_run -> right;    
    }

   return(NULL); 
}

void destroy_node(bst_node_t* p_root_node)
{
    if(p_root_node != NULL)
    {
        destroy_node(p_root_node->left);
        destroy_node(p_root_node->right);
        free(p_root_node);
    }
}

void preorder_node(bst_node_t* p_root_node)
{
    printf("[%d]<->", p_root_node->data);
    preorder_node(p_root_node->left);
    preorder_node(p_root_node->right);
}


void inorder_node(bst_node_t* p_root_node)
{
    inorder_node(p_root_node->left);
    printf("[%d]<->", p_root_node->data);
    inorder_node(p_root_node->right);
}

void postorder_node(bst_node_t* p_root_node)
{
    postorder_node(p_root_node->left);
    postorder_node(p_root_node->right);
    printf("[%d]<->", p_root_node->data);
}