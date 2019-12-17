/**
 * @file linked_list.c
 *
 * @brief Implementation of the linked list.
 *
 * @author Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca - Carleton University
 * @author Nhat Hieu Le - nhathieule@cmail.carleton.ca - Carleton University
 * @author Jason Miller - jasonmiller@cmail.carleton.ca - Carleton University
 */

#include "linked_list.h"

Node_t *create(int time, char *name, float value, Node_t *next)
{
    Node_t *new_node = malloc(sizeof(Node_t));
    if (!new_node)
    {
        /* This is a major issue, so we should abort the whole program. */
        printf("Error creating new node (malloc failed)\n");
        exit(0);
    }

    new_node->time_in_minutes = time;
    strncpy(new_node->sensor_name, name, MAX_SENSOR_NAME_SIZE);
    new_node->sensor_value = value;
    new_node->next = next;

    return new_node;
}

Node_t *append(Node_t *head, int time, char *name, float value)
{
    Node_t *node = head;
    Node_t *new_node;

    /* Creating node at end of list, so there is no next node to pass. */
    new_node = create(time, name, value, NULL);
    if (!node)
    {
        /*
         * The head pointer is NULL, which means we have nothing in our list
         * so far. We will assign the new node to the head pointer and return
         * that.
         */
        node = new_node;
        return node;
    }

    /*
     * We have elements in our list already, so we will traverse to the end of
     * the list and append the new node there.
     */
    while (node->next)
    {
        node = node->next;
    }

    node->next = new_node;
    return head;
}

Node_t *update(Node_t *head, int time, char *name, float value)
{
    Node_t *node = search_sensor_name(head, name);

    if (node == NULL)
    {
        /*
         * No found node, so we will just add the node to the end of the list.
         */
        return append(head, time, name, value);
    }

    node->time_in_minutes = time;
    node->sensor_value = value;
    return head;
}

Node_t *search_sensor_name(Node_t *head, char *str)
{
    Node_t *node = head;

    if (!str)
    {
        /*
         * Was given an invalid string to search, so we must abort.
         */
        return NULL;
    }

    while (node)
    {
        /*
         * Iterate over all nodes to see if there is a node that has the same
         * name as what we are searching for.
         */
        if (strcmp(node->sensor_name, str) == 0)
        {
            return node;
        }

        node = node->next;
    }

    return NULL;
}

Node_t *remove_from_front(Node_t *head)
{
    Node_t *node = head;

    if (!head)
    {
        /*
         * No list to even remove from, we can return and empty list.
         */
        return NULL;
    }

    head = head->next;
    node->next = NULL;

    if (node == head)
    {
        /*
         * We have removed the only entry in the list.
         */
        head = NULL;
    }

    free(node);
    return head;
}

Node_t *remove_from_back(Node_t *head)
{
    Node_t *node = head;
    Node_t *last = NULL;

    if (!head)
    {
        /*
         * We've been provided an invalid list, so we can just return NULL.
         */
        return NULL;
    }

    while (node->next)
    {
        last = node;
        node = node->next;
    }

    if (last)
    {
        last->next = NULL;
    }

    if (node == head)
    {
        head = NULL;
    }

    free(node);
    return head;
}

Node_t *remove_node(Node_t *head, Node_t *to_be_removed)
{
    Node_t *node = head;

    if (to_be_removed == head)
    {
        head = remove_from_front(head);
        return head;
    }

    if (to_be_removed->next == NULL)
    {
        head = remove_from_back(head);
        return head;
    }

    while (node)
    {
        /*
         * If the node we want to remove isn't the front or last, we can run
         * through the list to see if any node matches what we want to remove.
         */
        if (node->next == to_be_removed)
        {
            break;
        }
        node = node->next;
    }

    if (node)
    {
        Node_t *temp = node->next;
        node->next = temp->next;
        temp->next = NULL;
        free(temp);
    }

    return head;
}

Boolean move_node(Node_t *node, Node_t **head_move_from, Node_t **head_move_to)
{
    if (node)
    {
        *head_move_to = append(*head_move_to,
                               node->time_in_minutes,
                               node->sensor_name,
                               node->sensor_value);

        *head_move_from = remove_node(*head_move_from,
                                      node);
        return TRUE;
    }

    return FALSE;
}

void display(Node_t *head)
{
    Node_t *node = head;
    int i = 0;

    if (!node)
    {
        printf("Node is empty\n");
        return;
    }

    printf("Node data\n");
    while (node)
    {
        ++i;
        printf("Node %d\n", i);
        display_node(node);
        node = node->next;
    }
    printf("\n");
}

void display_node(Node_t *node)
{
    if (!node)
    {
        printf("Node is NULL\n");
        return;
    }

    printf("  Time:  %d\n", node->time_in_minutes);
    printf("  Name:  %s\n", node->sensor_name);
    printf("  Value: %0.2f\n\n", node->sensor_value);
}

int count(Node_t *head)
{
    Node_t *node = head;
    int count = 0;

    while (node != NULL)
    {
        ++count;
        node = node->next;
    }

    return count;
}
