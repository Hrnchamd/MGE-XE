#pragma once

#include <cstddef>



class MemoryPool {
public:
    MemoryPool(std::size_t object_size, std::size_t objects_per_block);
    void* Alloc();
    void Flush();
    ~MemoryPool();

private:
    class MemoryBlock {
    public:
        MemoryBlock(MemoryPool* owner);
        ~MemoryBlock();
        void* Alloc();

        MemoryBlock* next_block;

    private:
        MemoryPool* owner;
        std::size_t next_alloc;
        char* data;
    };

    void AllocFirstBlock();
    void FreeAllBlocks();

    MemoryBlock* first_block;
    MemoryBlock* last_block;
    std::size_t obj_size;
    std::size_t blk_size;
    std::size_t objs_per_block;
};
