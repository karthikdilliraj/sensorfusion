#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "parsing_csv_file.h"

/**
 * The sensor lists are split into three:
 *  Valid sensors
 *  Out of range sensor
 *  Stuck sensors
 */
#define MAX_SENSOR_LISTS    3
#define VALID_SENSOR_LIST   0
#define OOR_SENSOR_LIST     1
#define STUCK_SENSOR_LIST   2


typedef struct Linked_List_Node
{
    int     time_in_minutes;
    char    sensor_name[MAX_SENSOR_NAME_SIZE];
    float   sensor_value;

    struct Linked_List_Node *next;
} Node_t;

/**
 * Function:    create
 *
 * Parameters:
 *  time    [in]    The time in minutes
 *  *name   [in]    Sensor name of the node
 *  value   [in]    Sensor value of the node
 *  *next   [in]    Pointer to the next node in the linked list
 *
 * Creates a node with the specified information and assigns its next pointer
 * to the passed in *next
 *
 * Return:
 *  The newly created node object
 */
Node_t* create(int time, char *name, float value, Node_t *next);


/**
 * Function:    append
 *
 * Parameters:
 *  *head   [in]    Pointer to the head of a linked list chain
 *  time    [in]    The time in minutes
 *  *name   [in]    Sensor name of the node
 *  value   [in]    Sensor value of the node
 *
 * Appends a node with the specified information and places it at the end of
 * the linked list chain specified by *head.
 *
 * Return:
 *  Pointer to the head node
 */
Node_t* append(Node_t *head, int time, char *name, float value);


/**
 * Function:    update
 *
 * Parameters:
 *  *head   [in]    Pointer to the head of a linked list chain
 *  time    [in]    The time in minutes
 *  *name   [in]    Sensor name of the node
 *  value   [in]    Sensor value of the node
 *
 * Searches the linked list chain pointed to by *head for the sensor named
 * *name, if found it updates the node, otherwise it appends a new node with
 * the specified data to the end of the list.
 *
 * Return:
 *  Pointer to the head node
 */
Node_t* update(Node_t *head, int time, char *name, float value);


/**
 * Function:    search_sensor_name
 *
 * Parameters:
 *  *head   [in]    Pointer to the head of a linked list chain
 *  *str    [in]    Name of the sensor to search for
 *
 * Iterate over the linked list chain pointed to by head until it finds the
 * node that contains the sensor name that matches the passed in str.
 *
 * Return:
 *  Pointer to the matching node, if no node is found, returns NULL.
 */
Node_t* search_sensor_name(Node_t *head, char *str);


/**
 * Function:    remove_from_front
 *
 * Parameters:
 *  *head   [in]    Pointer to the head of a linked list chain
 *
 * Removes the first node in the linked list chain pointed to by head (ie: The
 * node that is pointed to by the head pointer).
 *
 * Return:
 *  Pointer to the head node.
 */
Node_t* remove_from_front(Node_t *head);


/**
 * Function:    remove_from_back
 *
 * Parameters:
 *  *head   [in]    Pointer to the head of a linked list chain
 *
 * Removes the last node in the linked list chain pointed to by head.
 *
 * Return:
 *  Pointer to the head node.
 */
Node_t* remove_from_back(Node_t *head);


/**
 * Function:    remove_node
 *
 * Parameters:
 *  *head           [in]    Pointer to the head of a linked list chain
 *  *to_be_removed  [in]    Pointer to the node to be removed
 *
 * Removes the specified node from the linked list chain pointed to by head.
 *
 * Return:
 *  Pointer to the head node.
 */
Node_t* remove_node(Node_t *head, Node_t *to_be_removed);


/**
 * Function:    move_node
 *
 * Parameters:
 *  **head_move_from    [in/out]    Pointer to the pointer of the head of the 
 *                                  linked list chain to move the node from
 *  **head_move_to      [in/out]    Pointer to the pointer of the head of the 
 *                                  linked list chain to move the node to
 *  *node               [in]        Pointer to the node to move
 *
 * Moves *node from the linked list chain pointed to by **head_move_from to the
 * linked list chain pointed to by **head_move_to.
 *
 * Return:
 *  True    - Node has been successfully moved
 *  False   - Node has not been successfully moved
 */
int move_node(Node_t **head_move_from, Node_t **head_move_to, Node_t *node);


/**
 * Function:    display_node
 *
 * Parameters:
 *  *node    [in]    Pointer to the node to be displayed
 *
 * Displays the time stamp, the sensor name and sensor value of the specified
 * node.
 *
 * Return:
 *  Nothing.
 */
void display_node(Node_t *node);


/**
 * Function:    display
 *
 * Parameters:
 *  *head    [in]    Pointer to the head of a linked list chain
 *
 * Displays the time stamp, the sensor name and sensor value of all nodes in
 * the linked list chain pointed to by head.
 *
 * Return:
 *  Nothing.
 */
void display(Node_t *head);


/**
 * Function:    count
 *
 * Parameters:
 *  *head    [in]    Pointer to the head of a linked list chain
 *
 * Counts all the nodes in the linked list chain pointed to by head.
 *
 * Return:
 *  Number of nodes in the linked list chain.
 */
int count(Node_t *head);

#endif
