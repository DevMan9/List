#include <assert.h>
#include <stdio.h>

#include "../source/list.x"

int ListIntCompare(const void *a, const void *b)
{
    if (**(int **)a > **(int **)b)
    {
        return 1;
    }
    else if (**(int **)a < **(int **)b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    struct List *list = NULL;
    printf("Creating list.\n");
    CreateList(&list);
    assert(list != NULL);

    int arr1[] = {1, 2, 3};
    printf("Adding items.\n");
    ListAdd(list, &(arr1[0]));
    ListAdd(list, &(arr1[1]));
    ListAdd(list, &(arr1[2]));

    for (size_t i = 0; i < 3; i++)
    {
        void *value = NULL;
        ListGetAt(list, i, &value);
        assert(*((int *)value) == arr1[i]);
    }

    printf("Removing index 0.\n");
    void *removed = NULL;
    ListRemoveAt(list, 0, &removed);
    assert(*((int *)removed) == 1);

    printf("Removing index 1.\n");
    ListAdd(list, removed);
    ListRemoveAt(list, 1, &removed);
    assert(*((int *)removed) == 3);

    printf("Removing index 2.\n");
    ListAdd(list, removed);
    ListRemoveAt(list, 2, &removed);
    assert(*((int *)removed) == 3);
    ListAdd(list, removed);

    printf("Checking size.\n");
    size_t size = 0;
    ListLength(list, &size);
    assert(size == 3);

    printf("Testing sort.\n");
    ListSortWithComparator(list, ListIntCompare);
    for (size_t i = 0; i < 3; i++)
    {
        void *value = NULL;
        ListGetAt(list, i, &value);
        assert(*((int *)value) == arr1[i]);
    }

    printf("Testing built in sort.\n");
    ListRemoveAt(list, 0, &removed);
    ListAdd(list, removed);
    ListSetComparator(list, ListIntCompare);
    ListSort(list);
    for (size_t i = 0; i < 3; i++)
    {
        void *value = NULL;
        ListGetAt(list, i, &value);
        assert(*((int *)value) == arr1[i]);
    }

    printf("Testing AddAt.\n");
    ListRemoveAt(list, 2, &removed);
    ListAddAt(list, removed, 1);

    void *got = NULL;
    ListGetAt(list, 0, &got);
    assert(*(int *)got == 1);
    ListGetAt(list, 1, &got);
    assert(*(int *)got == 3);
    ListGetAt(list, 2, &got);
    assert(*(int *)got == 2);

    printf("Testing ListToArray.\n");
    void **arr_out = NULL;
    ListToArray(list, &arr_out);
    assert(arr_out != NULL);
    assert(*((int *)(arr_out[0])) == 1);
    assert(*((int *)(arr_out[1])) == 3);
    assert(*((int *)(arr_out[2])) == 2);
    assert(arr_out[3] == NULL);

    printf("Testing resize grow.\n");
    for (int i = 0; i < 16; i++)
    {
        ListAdd(list, arr1);
    }
    ListLength(list, &size);
    assert(size == 19);
    assert(((size_t *)list)[1] == 32);

    printf("Testing resize shrink.\n");
    for (int i = 0; i < 16; i++)
    {
        ListRemoveAt(list, 0, NULL);
    }
    ListLength(list, &size);
    assert(size == 3);
    assert(((size_t *)list)[1] == 16);

    printf("Testing default find.\n");
    ssize_t found = -2;
    int find = 2;
    ListFind(list, &find, &found);
    assert(found = 2);

    printf("Testing find with.\n");
    find = 15;
    ListFindWithComparator(list, &find, ListIntCompare, &found);
    assert(found = -1);

    printf("Destroying list.\n");
    DestroyList(&list);
    assert(list == NULL);

    printf("All tests passed!\n");
    return 0;
}