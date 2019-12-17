/**
 * @file linked_list.h
 *
 * @brief Implementation of the linked list data structure.
 * Implements a linked list for the purposes of storing and sorting sensor input.
 *
 * @author Karthik Dilliraj - karthikdilliraj@cmail.carleton.ca - Carleton University
 * @author Nhat Hieu Le - nhathieule@cmail.carleton.ca - Carleton University
 * @author Jason Miller - jasonmiller@cmail.carleton.ca - Carleton University
 */

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "parsing_csv_file.h"

/**
 * @brief Maximum number of linked lists implemented by the program.
 */
#define MAX_SENSOR_LISTS    3

/**
 * @brief Valid sensors go into this list.
 */
#define VALID_SENSOR_LIST   0

/**
 * @brief Out of range sensor list.
 *
 * Sensors that are not within a valid range, specified by the user are placed
 * into this list.
 */
#define OOR_SENSOR_LIST     1

/**
 * @brief Stuck sensor list.
 *
 * Sensors that have not been updated within a given time, specified by the
 * user, are placed into this list.
 */
#define STUCK_SENSOR_LIST   2

/**
 * @brief Linked list implementation
 */
typedef struct Linked_List_Node {
    int     time_in_minutes;
    /**< Time converted from 24 hour clock to minutes */

    char    sensor_name[MAX_SENSOR_NAME_SIZE];
    /**< Name of the sensor */

    float   sensor_value;
    /**< Value being reported by the sensor */

    struct Linked_List_Node *next;
    /**< Pointer to the next node in the linked list (NULL if no more nodes) */
}
Node_t;


/**
 * @brief Creates a node
 *
 * @param[in] time      The time in minutes
 * @param[in] *name     Sensor name of the node
 * @param[in] value     Sensor value of the node
 * @param[in] *next     Pointer to the next node in the linked list
 *
 * @details Creates a node with the specified information and assigns its next
 * pointer to the passed in *next
 *
 * @return The newly created node object
 */
Node_t* create(int time, char *name, float value, Node_t *next);


/**
 * @brief Appends a node to the end of a linked list
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 * @param[in] time      The time in minutes
 * @param[in] *name     Sensor name of the node
 * @param[in] value     Sensor value of the node
 *
 * @details Appends a node with the specified information and places it at the
 * end of the linked list chain specified by *head.
 *
 * @return Pointer to the head node
 */
Node_t* append(Node_t *head, int time, char *name, float value);


/**
 * @brief Updates an existing node, or appends a new node
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 * @param[in] time      The time in minutes
 * @param[in] *name     Sensor name of the node
 * @param[in] value     Sensor value of the node
 *
 * @details Searches the linked list chain pointed to by *head for the sensor
 * named *name, if found it updates the node, otherwise it appends a new node
 * with the specified data to the end of the list.
 *
 * @return Pointer to the head node
 */
Node_t* update(Node_t *head, int time, char *name, float value);


/**
 * @brief Searches for a node within a linked list
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 * @param[in] *str      Name of the sensor to search for
 *
 * Iterate over the linked list chain pointed to by head until it finds the
 * node that contains the sensor name that matches the passed in str.
 *
 * Return:
 *  Pointer to the matching node, if no node is found, returns NULL.
 */
Node_t* search_sensor_name(Node_t *head, char *str);


/**
 * @brief Removes a node from the front of a linked list chain
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 *
 * @details Removes the first node in the linked list chain pointed to by head
 * (ie: The node that is pointed to by the head pointer).
 *
 * @return Pointer to the head node.
 */
Node_t* remove_from_front(Node_t *head);


/**
 * @brief Removes a node from the end of a linked list chain
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 *
 * @details Removes the last node in the linked list chain pointed to by head.
 *
 * @return Pointer to the head node.
 */
Node_t* remove_from_back(Node_t *head);


/**
 * @brief Removes a node specified by *to_be_removed
 *
 * @param[in] *head             Pointer to the head of a linked list chain
 * @param[in] *to_be_removed    Pointer to the node to be removed
 *
 * @details Removes the specified node from the linked list chain pointed to by
 * head.
 *
 * @return Pointer to the head node.
 */
Node_t* remove_node(Node_t *head, Node_t *to_be_removed);


/**
 * @brief Move a node between two linked lists
 *
 * @param[in]       *node               Pointer to the node to move
 * @param[in,out]   **head_move_from    Pointer to the pointer of the head of
 *                                      the linked list chain to move the node
 *                                      from
 * @param[in,out]   **head_move_to      Pointer to the pointer of the head of
 *                                      the linked list chain to move the node
 *                                      to
 *
 * @details Moves *node from the linked list chain pointed to by
 * **head_move_from to the linked list chain pointed to by **head_move_to.
 *
 * @return
 *  True    - Node has been successfully moved
 *  False   - Node has not been successfully moved
 */
Boolean move_node(Node_t *node, Node_t **head_move_from, Node_t **head_move_to);


/**
 * @brief Display the contents of a single node to the screen
 *
 * @param[in] *node     Pointer to the node to be displayed
 *
 * @details Displays the time stamp, the sensor name and sensor value of the
 * specified node.
 */
void display_node(Node_t *node);


/**
 * @brief Display the contents of all nodes in a linked list
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 *
 * @details Displays the time stamp, the sensor name and sensor value of all
 * nodes in the linked list chain pointed to by head.
 */
void display(Node_t *head);


/**
 * @brief Count how many nodes are in a linked list
 *
 * @param[in] *head     Pointer to the head of a linked list chain
 *
 * @details Counts all the nodes in the linked list chain pointed to by head.
 *
 * @return Number of nodes in the linked list chain.
 */
int count(Node_t *head);

#endif
