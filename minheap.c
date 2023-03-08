/*
 * Our min-heap implementation.
 *
 * Author (starter code): A. Tafliovich.
 */

#include "minheap.h"

#define ROOT_INDEX 1
#define NOTHING -1

/*************************************************************************
 ** Suggested helper functions
 *************************************************************************/

/* Returns True if 'maybeIdx' is a valid index in minheap 'heap', and 'heap'
 * stores an element at that index. Returns False otherwise.
 */
bool isValidIndex(MinHeap* heap, int maybeIdx){
    return (maybeIdx >= ROOT_INDEX && maybeIdx <= heap -> size);
}

/* Returns the index of the left child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such left
 * child.
 */
int leftIdx(MinHeap* heap, int nodeIndex){
    if(isValidIndex(heap, 2 * nodeIndex)){
        return nodeIndex * 2;
    }
    return NOTHING;
}

/* Returns the index of the right child of a node at index 'nodeIndex' in
 * minheap 'heap', if such exists.  Returns NOTHING if there is no such right
 * child.
 */
int rightIdx(MinHeap* heap, int nodeIndex){
    if(isValidIndex(heap, 2 * nodeIndex + 1)){
        return nodeIndex * 2 + 1;
    }
    return NOTHING;
}

/* Returns the index of the parent of a node at index 'nodeIndex' in minheap
 * 'heap', if such exists.  Returns NOTHING if there is no such parent.
 */
int parentIdx(MinHeap* heap, int nodeIndex){
    if(isValidIndex(heap, nodeIndex)){
        return nodeIndex / 2;
    }
    return NOTHING;
}

/* Returns priority of node at index 'nodeIndex' in minheap 'heap'.
 * Precondition: 'nodeIndex' is a valid index in 'heap'
 *               'heap' is non-empty
 */
int priorityAt(MinHeap* heap, int nodeIndex){

    return heap -> arr[nodeIndex].priority;
}

/* Swaps contents of heap->arr[index1] and heap->arr[index2] if both 'index1'
 * and 'index2' are valid indices for minheap 'heap'. Has no effect
 * otherwise.
 */
void swap(MinHeap* heap, int index1, int index2){
    if(isValidIndex(heap, index1) && isValidIndex(heap, index2)){
        HeapNode temp = heap -> arr[index1];
        heap -> arr[index1] = heap -> arr[index2];
        heap -> arr[index2] = temp;
        heap -> indexMap[heap -> arr[index1].id] = index1;
        heap -> indexMap[heap -> arr[index2].id] = index2;
    }
}

/* Bubbles up the element newly inserted into minheap 'heap' at index
 * 'nodeIndex', if 'nodeIndex' is a valid index for heap. Has no effect
 * otherwise.
 */
void bubbleUp(MinHeap* heap, int nodeIndex){

    if(isValidIndex(heap, nodeIndex)){
        int parent = parentIdx(heap, nodeIndex); 
        if(isValidIndex(heap, parent) && priorityAt(heap, parent) > priorityAt(heap, nodeIndex)){
            swap(heap, parent, nodeIndex);
            bubbleUp(heap, parent);
        }
    }
}

/* Bubbles down the element newly inserted into minheap 'heap' at the root,
 * if it exists. Has no effect otherwise.
 */
void bubbleDown(MinHeap* heap){

    if(heap == NULL || heap -> size <= 1){
        return;
    }

    int root = ROOT_INDEX;
    while (isValidIndex(heap, root)){
        int left = leftIdx(heap, root);
        int right = rightIdx(heap, root);
        int min = root;
        if(isValidIndex(heap, left) && priorityAt(heap, left) < priorityAt(heap, min)){
            min = left;
        }
        if(isValidIndex(heap, right) && priorityAt(heap, right) < priorityAt(heap, min)){
            min = right;
        }
        if(min != root){
            swap(heap, root, min);
            root = min;
        } else {
            break;
        }
    }
}

/* Doubles the capacity of minheap 'heap'.
 */
void doubleCapacity(MinHeap* heap){

    heap -> capacity *= 2;
    HeapNode *newArr = (HeapNode*)calloc(heap -> capacity + 1, sizeof(HeapNode));
    int* newIndexMap = (int*)calloc(heap -> capacity + 1, sizeof(int));

    for(int i = 1; i <= heap -> size; i++){
        newArr[i] = heap -> arr[i];
        newIndexMap[heap -> arr[i].id] = i;
    }
    for (int i = heap -> size + 1; i <= heap -> capacity; i++){
        newIndexMap[i] = NOTHING;
    }

    free(heap -> arr);
    free(heap -> indexMap);
    heap -> arr = newArr;
    heap -> indexMap = newIndexMap;
}

/*********************************************************************
 * Required functions
 ********************************************************************/

/* Returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode getMin(MinHeap* heap){
    
    return heap -> arr[ROOT_INDEX];
}

/* Removes and returns the node with minimum priority in minheap 'heap'.
 * Precondition: heap is non-empty
 */
HeapNode extractMin(MinHeap* heap){

    HeapNode root = heap -> arr[ROOT_INDEX];
    swap(heap, ROOT_INDEX, heap -> size);
    heap -> indexMap[root.id] = NOTHING;
    heap -> size--;
    bubbleDown(heap);
    return root;

}

/* Inserts a new node with priority 'priority' and value 'value' into minheap
 * 'heap'. If 'heap' is full, double the capacity of 'heap' before inserting
 * the new node.
 */
void insert(MinHeap* heap, int priority, void* value){

    if(heap -> size == heap -> capacity){
        doubleCapacity(heap);
    }

    heap -> size++;
    heap -> arr[heap -> size].priority = priority;
    heap -> arr[heap -> size].value = value;
    heap -> arr[heap -> size].id = heap -> size;
    heap -> indexMap[heap -> size] = heap -> size;
    bubbleUp(heap, heap -> size);
}

/* Sets priority of node with ID 'id' in minheap 'heap' to 'newPriority', if
 * such a node exists in 'heap' and its priority is larger than
 * 'newPriority', and returns True. Has no effect and returns False, otherwise.
 * Note: this function bubbles up the node until the heap property is restored.
 */
bool decreasePriority(MinHeap* heap, int id, int newPriority){

    int index = heap -> indexMap[id];
    if(index == NOTHING){
        return false;
    }
    if(newPriority > priorityAt(heap, index)){
        return false;
    }

    heap -> arr[index].priority = newPriority;
    bubbleUp(heap, index);
    return true;
}

/*********************************************************************
 ** Helper function provided in the starter code
 *********************************************************************/

/* Prints the contents of this heap, including size, capacity, full index
 * map, and, for each non-empty element of the heap array, that node's ID and
 * priority. */
void printHeap(MinHeap* heap) {
  printf("MinHip with size: %d\n\tcapacity: %d\n\n", heap->size,
         heap->capacity);
  printf("index: priority [ID]\t ID: index\n");
  for (int i = ROOT_INDEX; i <= heap->size; i++)
    printf("%d: %d [%d]\t\t%d: %d\n", i, heap->arr[i].priority, heap->arr[i].id,
           i, heap->indexMap[i]);
  for (int i = heap->size + 1; i <= heap->capacity; i++)
    printf("\t\t\t%d: %d\n", i, heap->indexMap[i]);
  printf("\n\n");
}

/*********************************************************************
 ** Helper functions not provided in the starter code
 *********************************************************************/

/* Returns a newly created empty minheap with initial capacity 'capacity'.
 * Precondition: capacity > 0
 */
MinHeap* newHeap(int capacity){

    MinHeap* heap = (MinHeap*)calloc(1, sizeof(MinHeap));
    heap -> arr = (HeapNode*)calloc(capacity + 1, sizeof(HeapNode));
    heap -> indexMap = (int*)calloc(capacity + 1, sizeof(int));

    heap -> capacity = capacity;
    heap -> size = 0;
    
    for (int i = 0; i <= capacity; i++){
        heap -> indexMap[i] = NOTHING;
    }
    return heap;
}

/* Frees all memory allocated for minheap 'heap'.
 */
void deleteHeap(MinHeap* heap){

    for (int i = 1; i <= heap -> size; i++){
        free(heap -> arr[i].value);
    }

    free(heap -> arr);
    free(heap -> indexMap);
    free(heap);

}

