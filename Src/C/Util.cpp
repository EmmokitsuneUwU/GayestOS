#include "Util.hpp"
#include "IO.hpp"
#define MAX_ARGS 5

int chainToInt(char *str)
{
    int result = 0;
    int i = 0;

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }

    return result;
}

bool StrCmp(const char* str1, const char* str2)
{
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return false;
        }
            str1++;
            str2++;
        }
    
    return (*str1 == '\0' && *str2 == '\0');
}
void reboot()
{
    while ((inb(0x64) & 0x02) != 0);
    outb(0x64, 0xFE); 
}
void cpyTBuffer(uint8_t *d, const char *o)
{
    while (*o) {
        *d = (uint8_t)*o;
        o++;
        d++;
    }
    *d = 0;
}
void cpyDatTBuffer(uint8_t *d, const char *o,unsigned int s)
{
    for (unsigned int i = 0; i < s; i++) {
        d[i] = (uint8_t)o[i];
    }
}

#include <stdint.h>
#include <stddef.h>

typedef struct block {
    size_t size;
    struct block* next;
    int free;
} block_t;

static block_t* free_list = NULL;
static void* heap_start = NULL;
static size_t heap_size = 0;

void simple_alloc_init(void* heap, size_t size) {
    heap_start = heap;
    heap_size = size;
    free_list = (block_t*)heap_start;
    free_list->size = heap_size - sizeof(block_t);
    free_list->next = NULL;
    free_list->free = 1;
}

void* simple_malloc(size_t size) {
    block_t *curr = free_list, *prev = NULL;
    while (curr) {
        if (curr->free && curr->size >= size) {
            if (curr->size > size + sizeof(block_t)) {
                block_t* new_block = (block_t*)((uint8_t*)curr + sizeof(block_t) + size);
                new_block->size = curr->size - size - sizeof(block_t);
                new_block->free = 1;
                new_block->next = curr->next;

                curr->size = size;
                curr->next = new_block;
            }
            curr->free = 0;
            return (void*)((uint8_t*)curr + sizeof(block_t));
        }
        prev = curr;
        curr = curr->next;
    }
    return NULL;
}

void simple_free(void* ptr) {
    if (!ptr) return;

    block_t* block = (block_t*)((uint8_t*)ptr - sizeof(block_t));
    block->free = 1;

    if (block->next && block->next->free) {
        block->size += sizeof(block_t) + block->next->size;
        block->next = block->next->next;
    }

    block_t* curr = free_list;
    while (curr && curr->next && curr->next != block) {
        curr = curr->next;
    }
    if (curr && curr->free && curr->next == block) {
        curr->size += sizeof(block_t) + block->size;
        curr->next = block->next;
    }
}