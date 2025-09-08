#include <stdlib.h>
#include <string.h>

#include "C-List-StandardContract/list.x"

size_t list_minimum_size = 16;

struct List
{
    size_t item_size;
    size_t item_count;
    size_t size;
    char *items;
    ListComparator comparator;
};

void CreateList(size_t item_size, struct List **ret)
{
    (*ret) = malloc(sizeof(**ret));
    (*ret)->item_size = item_size;
    (*ret)->item_count = 0;
    (*ret)->size = list_minimum_size;
    (*ret)->items = malloc((*ret)->size * (*ret)->item_size * sizeof(*((*ret)->items)));
    (*ret)->comparator = NULL;
}

void DestroyList(struct List **list_address)
{
    if (list_address == NULL)
    {
        goto skip;
    }
    free((*list_address)->items);
    free(*list_address);
    *list_address = NULL;
skip:
    return;
}

void ListSetComparator(struct List *list, ListComparator comparator)
{
    list->comparator = comparator;
}

static void _ListUpdateSize(struct List *list)
{
    if (list->item_count >= list->size)
    {
        list->size <<= 1;
    }
    else if ((list->size > list_minimum_size) && (list->item_count < (list->size >> 1)))
    {
        list->size >>= 1;
    }
    else
    {
        goto skip;
    }
    list->items = realloc(list->items, list->size * list->item_size * sizeof(*(list->items)));

skip:
    return;
}
void ListAdd(struct List *list, void *item)
{
    memcpy(list->items + list->item_count * list->item_size, item, list->item_size);
    list->item_count++;
    _ListUpdateSize(list);
}

void ListAddAt(struct List *list, void *item, size_t index)
{
    memmove(list->items + (index + 1) * list->item_size, list->items + index * list->item_size, (list->item_count - index) * list->item_size * sizeof(*(list->items)));
    memcpy(list->items + index * list->item_size, item, list->item_size);
    list->item_count++;
    _ListUpdateSize(list);
}

void ListGetAt(struct List *list, size_t index, void *ret)
{
    memcpy(ret, list->items + index * list->item_size, list->item_size);
}

void ListRemoveAt(struct List *list, size_t index, void *ret)
{
    if (ret != NULL)
    {
        memcpy(ret, list->items + index * list->item_size, list->item_size);
    }
    memmove(list->items + index * list->item_size, list->items + (index + 1) * list->item_size, (list->item_count - index - 1) * list->item_size * sizeof(*(list->items)));
    list->item_count--;
    _ListUpdateSize(list);
}

void ListSort(struct List *list)
{
    ListSortWithComparator(list, list->comparator);
}

void ListSortWithComparator(struct List *list, ListComparator comparator)
{
    qsort(list->items, list->item_count, list->item_size * sizeof(*(list->items)), comparator);
}

void ListToArray(struct List *list, void *ret)
{
    void **ret_alloc = ret;
    (*ret_alloc) = malloc(list->item_count * list->item_size * sizeof(*(list->items)));
    memcpy((*ret_alloc), list->items, list->item_count * list->item_size * sizeof(*(list->items)));
}

void ListLength(struct List *list, size_t *ret)
{
    (*ret) = list->item_count;
}

void ListFind(struct List *list, void *item, size_t *ret)
{
    ListFindWithComparator(list, item, list->comparator, ret);
}

void ListFindWithComparator(struct List *list, void *item, ListComparator comparator, size_t *ret)
{
    (*ret) = 0;
    while ((*ret) < list->item_count)
    {
        if (comparator(item, list->items + (*ret) * list->item_size) == 0)
        {
            break;
        }
        (*ret)++;
    }
    (*ret) = (*ret) < list->item_count ? (*ret) : -1;
}
