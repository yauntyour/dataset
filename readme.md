# dataset with C/C++

A dynamic array  with C/C++. Only used `calloc()` with `<stdlib.h>`

关于动态数组的概念就不多赘述了，dataset有一套完整的数据创建和效验，

您可以使用

```c
#define __dataset_null__ ((void *)0)
#define __dataset_end__ ((void *)-1)
#define __dataset_endVar__ ((void *)-2)
```

这三个宏来判断您的dataset是否合法。

除此之外，dataset本身不提供free的操作，我希望把操作权交给开发者；

因为free()的释放会影响迭代器的工作，这是由于free()并没有把头部设置为`__dataset_end__`，

所以我们建议您手动释放的同时自行设置头部，这边建议直接使用`reset_size()`重置dataset的大小。

这是相关的使用例子

```c
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

```

# 授权许可

100%完全开源，您可以自由使用此设计。用途由您自行决定。

**请保留作者出处**

This library was made by [yauntyour](https://github.com/yauntyour/).