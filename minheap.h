/*
 * Header file for our Priority Queue implementation.
 *
 * You will NOT be submitting this file. Your code will be tested with the
 * our own version of this file, so make sure you do not modify it!
 *
 * Author: A. Tafliovich.
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __MinHeap_header
#define __MinHeap_header

typedef struct heap_node {
  int priority;  // priority of this node
  void* value;   // value stored in this node
  int id;        // the unique ID of this node, 1 <= id <= size
} HeapNode;

typedef struct min_heap {
  int size;       // the number of nodes in this heap
  int capacity;   // the number of nodes that can be stored in this heap
  HeapNode* arr;  // the array that stores the nodes of this heap
  int* indexMap;  // indexMap[id] is the index of node with ID id in array arr
} MinHeap;

/* Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap);

/* Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap);

/* Inserts a new node with priority 'priority' and value 'value' into minheap
 * 'heap'. If 'heap' is full, double the capacity of 'heap' before inserting
 * the new node.
 */
void insert(MinHeap* heap, int priority, void* value);

/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority);

/* Prints the contents of this heap, including size, capacity, full index
 * map, and, for each non-empty element of the heap array, that node's ID and
 * priority. */
void printHeap(MinHeap* heap);

/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity > 0
 */
MinHeap* newHeap(int capacity);

/* Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap);

#endif
