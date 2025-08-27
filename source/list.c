#include <stdlib.h>
#include <string.h>

#include "list.x"

size_t list_minimum_size = 16;

struct List
{
    size_t item_count;
    size_t list_size;
    void **items;
    ListComparator comparator;
};

void CreateList(struct List **ret)
{
    (*ret) = malloc(sizeof(**ret));
    (*ret)->item_count = 0;
    (*ret)->list_size = list_minimum_size;
    (*ret)->items = malloc((*ret)->list_size * sizeof(*((*ret)->items)));
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
    if (list->item_count >= list->list_size)
    {
        list->list_size <<= 1;
    }
    else if ((list->list_size > list_minimum_size) && (list->item_count < (list->list_size >> 1)))
    {
        list->list_size >>= 1;
    }
    else
    {
        goto skip;
    }
    list->items = realloc(list->items, list->list_size * sizeof(*(list->items)));

skip:
    return;
}
void ListAdd(struct List *list, void *item)
{
    list->items[list->item_count] = item;
    list->item_count++;
    _ListUpdateSize(list);
}

void ListAddAt(struct List *list, void *item, size_t index)
{
    memmove(list->items + index + 1, list->items + index, (list->item_count - index) * sizeof(*(list->items)));
    list->items[index] = item;
    list->item_count++;
    _ListUpdateSize(list);
}

void ListGetAt(struct List *list, size_t index, void **ret)
{
    (*ret) = list->items[index];
}

void ListRemoveAt(struct List *list, size_t index, void **ret)
{
    if (ret != NULL)
    {
        (*ret) = list->items[index];
    }
    memmove(list->items + index, list->items + index + 1, (list->item_count - index - 1) * sizeof(*(list->items)));
    list->item_count--;
    _ListUpdateSize(list);
}

void ListSort(struct List *list)
{
    qsort(list->items, list->item_count, sizeof(*(list->items)), list->comparator);
}

void ListSortWithComparator(struct List *list, ListComparator comparator)
{
    qsort(list->items, list->item_count, sizeof(*(list->items)), comparator);
}

void ListToArray(struct List *list, void ***ret)
{
    (*ret) = malloc((1 + list->item_count) * sizeof(*(list->items)));
    memcpy((*ret), list->items, list->item_count * sizeof(*(list->items)));
    (*ret)[list->item_count] = NULL;
}

void ListLength(struct List *list, size_t *ret)
{
    (*ret) = list->item_count;
}

void ListFind(struct List *list, void *item, ssize_t *ret)
{
    ListFindWithComparator(list, item, list->comparator, ret);
}

void ListFindWithComparator(struct List *list, void *item, ListComparator comparator, ssize_t *ret)
{
    (*ret) = 0;
    while ((*ret) < list->item_count)
    {
        if (comparator(&item, &(list->items[(*ret)])) == 0)
        {
            break;
        }
        (*ret)++;
    }
    (*ret) = (*ret) < list->item_count ? (*ret) : -1;
}
