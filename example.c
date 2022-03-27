#include <stdio.h>
#include "dataset.h"

int main(int argc, char const *argv[])
{
    dataset set = dataset_create(5);
    /*for each and set data*/
    for (size_t i = 0;; i++)
    {
        set[i].data = &i;
        if (set[i].point == __dataset_end__)
        {
            break;
        }
        if (set[i].point == __dataset_endVar__)
        {
            set[i].point = __dataset_null__;
        }
    }
    /*for each and out*/
    for (size_t i = 0;; i++)
    {
        printf("%d:%d\n", i, *((int *)set[i].data));
        if (set[i].point == __dataset_end__ || set[i].point == __dataset_endVar__)
        {
            break;
        }
    }
    printf("size:%d\n", dataset_sizeof(&set));
    printf("length:%d\n\n", dataset_length(&set));

    /*addend n* elements*/
    __Var__ v;
    v.data = "hi";
    dataset_addendn(&set, 3, &v, &v, &v);

    printf("size:%d\n", dataset_sizeof(&set));
    printf("length:%d\n\n", dataset_length(&set));

    /*reset the size of dataset*/
    dataset_reset_size(&set, 10);
    for (size_t i = 0;; i++)
    {
        printf("%d:%d\n", i, *((int *)set[i].data));
        if (set[i].point == __dataset_end__ || set[i].point == __dataset_endVar__)
        {
            break;
        }
    }
    printf("size:%d\n", dataset_sizeof(&set));
    printf("length:%d\n\n", dataset_length(&set));

    /*dataset cating for two set with one by one*/
    dataset buf = dataset_create(5);
    for (size_t i = 0;; i++)
    {
        buf[i].data = &i;
        if (buf[i].point == __dataset_end__)
        {
            break;
        }
        if (buf[i].point == __dataset_endVar__)
        {
            buf[i].point = __dataset_null__;
        }
    }
    dataset_cat(&set, &buf);

    printf("size:%d\n", dataset_sizeof(&set));
    printf("length:%d\n", dataset_length(&set));

    for (size_t i = 0;; i++)
    {
        printf("%d:%d\n", i, *((int *)set[i].data));
        if (set[i].point == __dataset_end__ || set[i].point == __dataset_endVar__)
        {
            break;
        }
    }
    /*
    Did you want to free the dataset?
    oh,it's nothing.
    Then you didn't worry about the memory.
    It such as a array,but it's a dynamic array.
    Just like a variable.
    In the codes,I am just used calloc() to make memory spare.
    Nothing to free.
    But,sometimes as you like what to do.
    */
    return 0;
}
