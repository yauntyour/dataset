#ifndef __DATASET__H__
#define __DATASET__H__
#include <stdlib.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif
    // self's type.
    typedef unsigned long long size_t;

    typedef unsigned short bool;
#define True 1
#define False 0

    typedef struct var
    {
        struct var *point;
        void *data;
    } __Var__;
    typedef __Var__ *dataset;

#define __dataset_null__ ((void *)0)
#define __dataset_end__ ((void *)-1)
#define __dataset_endVar__ ((void *)-2)

    extern dataset dataset_create(size_t begin_size)
    {
        dataset set = (dataset)calloc(begin_size, sizeof(__Var__));
        set[begin_size - 1].point = __dataset_end__;
        for (size_t i = 0; set[i].point != __dataset_end__; i++)
        {
            set[i].data = NULL;
            set[i].point = __dataset_null__;
        }
        set[0].point = __dataset_endVar__;
        return set;
    }

    extern bool dataset_reset_size(dataset *set, size_t reset_size)
    {
        dataset temp = (dataset)calloc(reset_size, sizeof(__Var__));
        temp[reset_size - 1].point = __dataset_end__;
        size_t i = 0;
        while (temp[i].point != __dataset_end__)
        {
            temp[i].data = (*set)[i].data;
            if ((*set)[i].point == __dataset_endVar__ || (*set)[i].point == __dataset_end__)
            {
                temp[i].point = __dataset_endVar__;
                break;
            }
            i += 1;
        }
        *set = temp;
        return True;
    }

    extern size_t dataset_length(dataset *set)
    {
        size_t i = 0;
        while ((*set)[i].point != __dataset_endVar__ && (*set)[i].point != __dataset_end__)
        {
            i += 1;
        }
        return i + 1;
    }

    extern size_t dataset_sizeof(dataset *set)
    {
        size_t i = 0;
        while ((*set)[i].point != __dataset_end__)
        {
            i += 1;
        }
        return i + 1;
    }

    extern bool dataset_addend(dataset *set, __Var__ *v)
    {
        size_t length = dataset_length(set);
        size_t size = dataset_sizeof(set);

        if (length + 1 <= size)
        {
            (*set)[length] = *v;
            (*set)[length - 1].point = __dataset_null__;

            if (length + 1 == size)
            {
                (*set)[length].point = __dataset_end__;
            }
            (*set)[length].point = __dataset_endVar__;
        }
        else
        {
            dataset temp = (dataset)calloc(size + 1, sizeof(__Var__));

            temp[size] = *v;
            temp[size].point = __dataset_end__;
            temp[size - 1] = (*set)[size - 1];
            temp[size - 1].point = __dataset_null__;

            for (size_t i = 0; (*set)[i].point != __dataset_end__; i++)
            {
                temp[i] = (*set)[i];
            }
            *set = temp;
        }
        return True;
    }

    extern bool dataset_addendn(dataset *set, size_t n, ...)
    {
        va_list valist;
        va_start(valist, n);

        size_t length = dataset_length(set);
        size_t size = dataset_sizeof(set);

        if (length + n <= size)
        {
            (*set)[length - 1].point = __dataset_null__;
            for (size_t i = 0; i < n; i++)
            {
                (*set)[length + i] = *(va_arg(valist, __Var__ *));
                (*set)[length + i].point = __dataset_null__;
            }
            if (length + n == size)
            {
                (*set)[length - 1 + n].point = __dataset_end__;
            }
            (*set)[length - 1 + n].point = __dataset_endVar__;
        }
        else
        {
            dataset temp = (dataset)calloc(size + n, sizeof(__Var__));

            for (size_t i = 0; i < n; i++)
            {
                temp[size + i] = *(va_arg(valist, __Var__ *));
                temp[size + i].point = __dataset_null__;
            }
            temp[size - 1 + n].point = __dataset_end__;

            temp[size - 1] = (*set)[size - 1];
            temp[size - 1].point = __dataset_null__;

            for (size_t i = 0; (*set)[i].point != __dataset_end__; i++)
            {
                temp[i] = (*set)[i];
            }
            *set = temp;
        }
        va_end(valist);
        return True;
    }

    extern bool dataset_cat(dataset *set, dataset *catend)
    {
        size_t set_size = dataset_sizeof(set);
        size_t catend_size = dataset_sizeof(catend);
        dataset temp = dataset_create(set_size + catend_size);
        size_t i = 0;
        for (;; i += 1)
        {
            temp[i] = (*set)[i];
            if ((*set)[i].point == __dataset_endVar__ || (*set)[i].point == __dataset_end__)
            {
                temp[i].point = __dataset_null__;
                break;
            }
        }
        for (size_t j = 0;; j++)
        {
            temp[i + 1 + j] = (*catend)[j];
            if ((*catend)[j].point == __dataset_end__ || (*catend)[j].point == __dataset_endVar__)
            {
                temp[i + 1 + j].point = __dataset_endVar__;
                break;
            }
        }
        temp[set_size + catend_size - 1].point = __dataset_end__;
        *set = temp;
        return True;
    }

#ifdef __cplusplus
}
#endif
#endif //!__DATASET__H__