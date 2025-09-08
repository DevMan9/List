#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "C-List-StandardContract/list.x"

int ListIntCompare(const void *a, const void *b)
{
    if (*(int *)a > *(int *)b)
    {
        return 1;
    }
    else if (*(int *)a < *(int *)b)
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
    CreateList(sizeof(int), &list);

    int test_arr[] = {5, 2, 1, 4, 8};

    for (size_t i = 0; i < 5; i++)
    {
        ListAdd(list, test_arr + i);
    }

    int get = -1;
    ListGetAt(list, 1, &get);
    printf("%d =?= %d\n", get, 2);
    assert(get == 2);

    ListGetAt(list, 0, &get);
    printf("%d =?= %d\n", get, 5);
    assert(get == 5);

    ListGetAt(list, 2, &get);
    printf("%d =?= %d\n", get, 1);
    assert(get == 1);

    ListSetComparator(list, ListIntCompare);

    ListSort(list);

    ListGetAt(list, 0, &get);
    printf("%d =?= %d\n", get, 1);
    assert(get == 1);

    ListGetAt(list, 1, &get);
    printf("%d =?= %d\n", get, 2);
    assert(get == 2);

    ListGetAt(list, 2, &get);
    printf("%d =?= %d\n", get, 4);
    assert(get == 4);

    size_t pos = -1;
    get = 4;
    ListFind(list, &get, &pos);
    printf("%zu =?= %zu\n", pos, (size_t)2);
    assert(pos == 2);

    get = 6;
    ListFind(list, &get, &pos);
    printf("%zu =?= %zu\n", pos, (size_t)-1);
    assert(pos == -1);

    get = 8;
    ListFind(list, &get, &pos);
    printf("%zu =?= %zu\n", pos, (size_t)4);
    assert(pos == 4);

    size_t len = 0;
    ListLength(list, &len);
    printf("%zu =?= %zu\n", len, (size_t)5);
    assert(len == 5);

    ListRemoveAt(list, 2, NULL);
    int *arr = NULL;
    ListToArray(list, &arr);
    ListLength(list, &len);
    printf("%zu =?= %zu\n", len, (size_t)4);
    assert(len == 4);

    int expected[] = {1, 2, 5, 8};
    for (size_t i = 0; i < len; i++)
    {
        ListGetAt(list, i, &get);
        printf("%d =?= %d\n", get, expected[i]);
        assert(get == expected[i]);
    }
    free(arr);

    DestroyList(&list);
    assert(list == NULL);

    printf("All tests passed!\n");
    return 0;
}