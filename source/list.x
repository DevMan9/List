#ifndef STANDARD_LIST_X_0
#define STANDARD_LIST_X_0

#include <stddef.h>

struct List;
typedef int (*ListComparator)(const void *, const void *);

// Constructor.
// Returns a newly allocated list.
void CreateList(struct List **ret);

// Destructor.
// Destroys an allocated list.  Sets given address to NULL after.
void DestroyList(struct List **list_address);

// Set the default comparator for the list.
void ListSetComparator(struct List *list, ListComparator comparator);

// Add an item to the end of the list.
void ListAdd(struct List *list, void *item);

// Add an item at the specified index.
void ListAddAt(struct List *list, void *item, size_t index);

// Get the item at the specified index.
void ListGetAt(struct List *list, size_t index, void **ret);

// Remove the item at the specificed index.
void ListRemoveAt(struct List *list, size_t index, void **ret);

// Sort the list according to its default comparator.
void ListSort(struct List *list);

// Sort the list according to the given comparator.
void ListSortWithComparator(struct List *list, ListComparator comparator);

// Create a NULL terminated array from the list.
void ListToArray(struct List *list, void ***ret);

// Get the number of elements in the list.
void ListLength(struct List *list, size_t *ret);

// Get the first index of an item that matches the given item according to the default comparator.
// Returns -1 if not found.
void ListFind(struct List *list, void *item, ssize_t *ret);

// Get the first index of an item that matches the given item according to the given comparator.
// Returns -1 if not found.
void ListFindWithComparator(struct List *list, void *item, ListComparator comparator, ssize_t *ret);

#endif // STANDARD_LIST_X_0