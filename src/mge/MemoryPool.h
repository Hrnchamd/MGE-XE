#ifndef _MEMORY_POOL_H_
#define _MEMORY_POOL_H_

#include <stddef.h>

class MemoryPool {
public:
    MemoryPool(size_t object_size, size_t objects_per_block);
    void * Alloc();
    void Flush();
    ~MemoryPool();

private:
    class MemoryBlock {
    public:
        MemoryBlock(MemoryPool* owner);
        ~MemoryBlock();
        void * Alloc();

        MemoryBlock *next_block;

    private:
        MemoryPool *owner;
        size_t next_alloc;
        size_t obj_count;
        unsigned char *data;
    };

    void AllocFirstBlock();
    void FreeAllBlocks();

    MemoryBlock *first_block;
    MemoryBlock *last_block;
    size_t obj_size;
    size_t blk_size;
    size_t objs_per_block;
};

#endif
