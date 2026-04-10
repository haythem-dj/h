#ifndef H_H_
#define H_H_

#include <stdlib.h>

#define H_DA_INIT_CAPACITY 10
#define H_DA_CAPACITY_FACTOR 2

typedef struct
{
    size_t count;
    size_t capacity;
} H_DA_Header;

#define h_da_header(arr) ((H_DA_Header*)(arr) - 1)

#define h_da_reserve(arr, n)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        H_DA_Header* h = (H_DA_Header*)malloc(sizeof(H_DA_Header) + sizeof(*(arr)) * n);                               \
        if (!h)                                                                                                        \
        {                                                                                                              \
            perror("malloc failed");                                                                                   \
            exit(EXIT_FAILURE);                                                                                        \
        }                                                                                                              \
        h->capacity = n;                                                                                               \
        h->count = 0;                                                                                                  \
        (arr) = (void*)(h + 1);                                                                                        \
    } while (0)

#define h_da_append(arr, x)                                                                                            \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((arr) == NULL)                                                                                             \
        {                                                                                                              \
            h_da_reserve(arr, H_DA_INIT_CAPACITY);                                                                     \
        }                                                                                                              \
        H_DA_Header* h = h_da_header((arr));                                                                           \
        if (h->count >= h->capacity)                                                                                   \
        {                                                                                                              \
            h->capacity *= H_DA_CAPACITY_FACTOR;                                                                       \
            h = realloc(h, sizeof(H_DA_Header) + h->capacity * sizeof(*(arr)));                                        \
            if (!h)                                                                                                    \
            {                                                                                                          \
                perror("realloc failed");                                                                              \
                exit(EXIT_FAILURE);                                                                                    \
            }                                                                                                          \
            (arr) = (void*)(h + 1);                                                                                    \
        }                                                                                                              \
        (arr)[h->count++] = (x);                                                                                       \
    } while (0)

#define h_da_size(arr) ((arr) != NULL ? h_da_header((arr))->count : 0)
#define h_da_capacity(arr) ((arr) != NULL ? h_da_header((arr))->capacity : 0)

#define h_da_free(arr)                                                                                                 \
    do                                                                                                                 \
    {                                                                                                                  \
        free(h_da_header((arr)));                                                                                      \
        (arr) = NULL;                                                                                                  \
    } while (0)

#define H_Linked_List(T)                                                                                               \
    struct                                                                                                             \
    {                                                                                                                  \
        T value;                                                                                                       \
        void* next;                                                                                                    \
    }*

#define h_ll_push_front(ll, v)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        __typeof__(ll) node = malloc(sizeof(*(ll)));                                                                   \
        if (!node)                                                                                                     \
        {                                                                                                              \
            perror("malloc failed.");                                                                                  \
            exit(EXIT_FAILURE);                                                                                        \
        }                                                                                                              \
        node->value = v;                                                                                               \
        node->next = (ll);                                                                                             \
        (ll) = node;                                                                                                   \
    } while (0)

#define h_ll_push_back(ll, v)                                                                                          \
    do                                                                                                                 \
    {                                                                                                                  \
        __typeof__(ll) node = malloc(sizeof(*(ll)));                                                                   \
        if (!node)                                                                                                     \
        {                                                                                                              \
            perror("malloc failed.");                                                                                  \
            exit(EXIT_FAILURE);                                                                                        \
        }                                                                                                              \
        node->value = v;                                                                                               \
        node->next = NULL;                                                                                             \
        if ((ll) == NULL) (ll) = node;                                                                                 \
        else                                                                                                           \
        {                                                                                                              \
            __typeof__(ll) cur = (ll);                                                                                 \
            while (cur->next) cur = cur->next;                                                                         \
            cur->next = node;                                                                                          \
        }                                                                                                              \
    } while (0)

#define h_ll_pop_front(ll)                                                                                             \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((ll) != NULL)                                                                                              \
        {                                                                                                              \
            __typeof__(ll) dead = (ll);                                                                                \
            (ll) = (ll)->next;                                                                                         \
            free(dead);                                                                                                \
        }                                                                                                              \
    } while (0)

#define h_ll_pop_back(ll)                                                                                              \
    do                                                                                                                 \
    {                                                                                                                  \
        if ((ll))                                                                                                      \
        {                                                                                                              \
            __typeof__(ll) cur = (ll);                                                                                 \
            __typeof__(ll) prv;                                                                                        \
            while ((cur)->next)                                                                                        \
            {                                                                                                          \
                prv = cur;                                                                                             \
                cur = cur->next;                                                                                       \
            }                                                                                                          \
            free(cur);                                                                                                 \
            prv->next = NULL;                                                                                          \
        }                                                                                                              \
    } while (0)

#define h_ll_free(ll)                                                                                                  \
    do                                                                                                                 \
    {                                                                                                                  \
        __typeof__(ll) cur = ll;                                                                                       \
        while (cur)                                                                                                    \
        {                                                                                                              \
            cur = ll->next;                                                                                            \
            free(ll);                                                                                                  \
            ll = cur;                                                                                                  \
        }                                                                                                              \
    } while (0)

#endif
