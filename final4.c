/* Project Title : Friend Management System
    Group Members : 24MCA053 - Shah Aarchi Vikaskumar , 
                    24MCA057 - Soni Kriyanshi Sanjaybhai
                    
    Course : 6CS102CC22 - Data Structure
    Academic Year : 2024-25
    MCA 1st Semester*/




#include <stdio.h>
#include <stdlib.h>
#define MAX_USERS 100

struct tree_node {
    char name; 
    int id;
    struct tree_node *left;
    struct tree_node *right;
};


struct adj_list_node {
    int id;
    struct adj_list_node *next;
};


typedef struct tree_node TNode;
typedef struct adj_list_node AdjNode;


TNode *create_tree_node(int id, char name) 
{
    TNode *new_node = (TNode *)malloc(sizeof(TNode));
    if (!new_node) 
    {
        printf("\n Memory Allocation Failed");
        return NULL;
    }
    new_node->id = id;
    new_node->name = name;
    id_to_name[id] = name;
    new_node->left = new_node->right = NULL;
    return new_node;
}

TNode *insert_tree_node(TNode *root, int id, char name) 
{
    if (root == NULL) 
    {
        return create_tree_node(id, name);
    }

    if (name < root->name) 
    {
        root->left = insert_tree_node(root->left, id, name);
    } 
    else if (name > root->name) {
        root->right = insert_tree_node(root->right, id, name);
    }

    return root;
}


int search_user_id(TNode *root, char name) 
{
    if (root == NULL) 
    {
        return -1;
    }

    if (root->name == name) 
    {
        return root->name;
    }

    if (name < root->name) 
    {
        return search_user_id(root->left, name);
    }
    return search_user_id(root->right, name);
}


AdjNode *create_adj_node(int id) 
{
    AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));

    if (new_node==NULL)
    {
        printf("\n Memory Allocation Failed");
        return NULL;
    }

    new_node->id = id;
    new_node->next = NULL;

    return new_node;
}


void add_friendship(int id1, int id2) 
{
    AdjNode *new_friend1 = create_adj_node(id2);
    new_friend1->next = friendship_list[id1];
    friendship_list[id1] = new_friend1;

    AdjNode *new_friend2 = create_adj_node(id1);
    new_friend2->next = friendship_list[id2];
    friendship_list[id2] = new_friend2;

    printf("\n Friendship added between %c and %c", id_to_name[id1], id_to_name[id2]);
}


void suggest_friends(TNode *root) 
{
    if (root == NULL) 
    {
        return; 
    }

    suggest_friends(root->left); 
    printf("Suggested Friend: %c\n", root->name); 
    suggest_friends(root->right); 
}


void find_mutual_friends_by_names(TNode *root, char name1, char name2) 
{
    int id1 = search_user_id(root, name1);
    int id2 = search_user_id(root, name2);

    if (id1 == -1 || id2 == -1) 
    {
        printf("\n One or both users not found in the network.\n");
        return;
    }

    AdjNode *list1 = friendship_list[id1];
    AdjNode *list2 = friendship_list[id2];

    printf("\n Mutual Friends between %c and %c: ", name1, name2);

    int found = 0;
    while (list1) 
    {
        AdjNode *temp = list2;
        while (temp) 
        {
            if (list1->id == temp->id) 
            {
                printf("%c ", id_to_name[list1->id]);
                found = 1;
                break;
            }
            temp = temp->next;
        }
        list1 = list1->next;
    }

    if (!found) 
    {
        printf("None");
    }
    printf("\n");
}


int main() 
{
    TNode *root = NULL;
    int id_counter = 0, choice;
    char name, name1, name2;

    printf("\n Friend Suggestion System with Friendships\n");
    while (1) 
    {
        printf("\n 1. Add a Friend");
        printf("\n 2. Search for a Friend");
        printf("\n 3. Suggest Friends");
        printf("\n 4. Add a Friendship");
        printf("\n 5. Find Mutual Friends by Names");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1:
                printf("\n Enter Friend Name (Single Character): ");
                scanf(" %c", &name);

                if (search_user_id(root, name) != -1) 
                {
                    printf("\n Friend with name %c already exists.", name);
                } 
                else 
                {
                    root = insert_tree_node(root, id_counter++, name);
                    printf("\n Friend with name %c added.", name);
                }
                break;

            case 2:
                printf("\n Enter Friend Name to Search (Single Character): ");
                scanf(" %c", &name);

                if (search_user_id(root, name) != -1) 
                {
                    printf("\n Friend with name %c exists in the network.", name);
                } 
                else 
                {
                    printf("\n Friend with name %c not found.", name);
                }
                break;

            case 3:
                if (root == NULL) 
                {
                    printf("\n No friends to suggest. Add some friends first!\n");
                } 
                else 
                {
                    printf("\n Friend Suggestions:\n");
                    suggest_friends(root);
                }
                break;

            case 4:
                printf("\n Enter two friend names to add friendship (Single Characters): ");
                scanf(" %c %c", &name1, &name2);

                int id1 = search_user_id(root, name1);
                int id2 = search_user_id(root, name2);

                if (id1 != -1 && id2 != -1) 
                {
                    add_friendship(id1, id2);
                } 
                else 
                {
                    printf("\n One or both users not found.");
                }
                break;

            case 5:
                printf("\n Enter the names of two friends to find mutual friends (Single Characters): ");
                scanf(" %c %c", &name1, &name2);
                find_mutual_friends_by_names(root, name1, name2);
                break;

            default:
                printf("\n Invalid Choice. Try Again.");
        }
    }
    return 0;
}
