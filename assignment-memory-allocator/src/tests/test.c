#include "test.h"
#include "mem_internals.h"
#include "mem.h"
#include "util.h"


static struct block_header* block_get_header(void* contents) {
  return (struct block_header*) (((uint8_t*)contents)-offsetof(struct block_header, contents));
}

static void* heap_init_tests() {
    void* heap = heap_init(REGION_MIN_SIZE);
    struct block_header *block = (struct block_header *) heap;

    if (!heap || !block) {
        err("smth went wrong:(");
        return NULL;
    }

    return heap;
}


bool test_allocate_one_block(struct block_header *heap) {
    fputs("Starting test 1...\n", stdout);
    void* heap1 = _malloc(1024);

    if (heap1 == NULL) {
        fputs("test 1 failed:(", stderr);
        return false;

    }
    
    fputs("everything is ok\n", stdout); 
    
    struct block_header *block = block_get_header(heap1);

    debug_heap(stdout, heap);


    if ((block->is_free || block->capacity.bytes != 1024)) {
        fputs("test 1 failed:((\n", stderr);
        return false;
    }
    
    fputs("test 1 successfully passed\n", stdout);
    
    _free(heap1);

    return true;

}

bool test_free_one_block(struct block_header *heap) {
    fputs("Starting test 2...\n", stdout);
    void* heap1 = _malloc(1024);
    void* heap2 = _malloc(2048);

    if (heap1 == NULL || heap2 == NULL) {
        fputs("test 2 failed:(\n", stderr);
        return false;
    }
    else {
        fputs("everything is ok\n", stdout);     
    }

    struct block_header *block1 = block_get_header(heap1);
    // struct block_header *block2 = block_get_header(heap2);
    debug_heap(stdout, heap);

    _free(heap1);

    if (!block1->is_free) {
        fputs("test 2 failed:(\n", stderr);
        return false;       
    }

    else {
        fputs("everything is ok\n", stdout);
        fputs("test 2 successfully passed\n", stdout);
    }
        
    debug_heap(stdout, heap); 

    _free(heap2);
    return true;
}

bool test_free_two_blocks(struct block_header *heap) {
    fputs("Starting test 3...\n", stdout);
    void* heap1 = _malloc(1000);
	void* heap2 = _malloc(1000);
	void* heap3 = _malloc(1000);
	
	if (heap1 == NULL || heap2 == NULL || heap3 == NULL) {
        fputs("test 3 failed:(\n", stderr);
        return false;
    }

    else {
        fputs("everything is ok\n", stdout);
    }

	
	_free(heap1);
	_free(heap3);
	debug_heap(stdout, heap);
	
	struct block_header* heap1_block = block_get_header(heap1);
	struct block_header* heap2_block = block_get_header(heap2);
	struct block_header* heap3_block = block_get_header(heap3);
	if (heap1_block->is_free == false || heap2_block->is_free == true || heap3_block->is_free == false) {
        fputs("test 3 failed:((\n", stderr);
        return false;
    }
	else {
        fputs("everything is ok\n", stdout);
        fputs("test 3 successfully passed\n", stdout);
    }
    

	_free(heap1);
	_free(heap2);
	_free(heap3);
    return true;
}

bool test_expand_region(struct block_header *heap) {
    fputs("Starting test 4...\n", stdout);
    void* heap1 = _malloc(420);

    if (heap1 == NULL) {
        fputs("test 4 failed:(\n", stderr);
        return false;
    }
    else {
        fputs("everything is ok\n", stdout);
    }
    struct block_header *block = (struct block_header *) heap1;
    debug_heap(stdout, heap);
    if (block_get_header(block)->capacity.bytes==420) {
        fputs("test 4 successfully passed\n", stdout);
    }

    else {
        fputs("test 4 failed:((\n", stderr);
        return false;
    }


    _free(heap1);
    return true;
}

bool test_complex_expend_region(struct block_header *heap) {
    fputs("Starting test 5...\n", stdout);
    void* heap1 = _malloc(2048);
    void* heap2 = _malloc(2048);

    if (heap1 == NULL || heap2 == NULL) {
        fputs("test 5 failed:(\n", stderr);
        return false;
    }
    else {
        fputs("everything is ok\n", stdout);
        fputs("test 5 successfully passed\n", stdout);
    }

    debug_heap(stdout, heap);


    _free(heap1);
    _free(heap2);
    return true;
}

bool run_all() {
    struct block_header *first_block = (struct block_header*) heap_init_tests();
    bool results = {test_allocate_one_block(first_block) && 
    test_free_one_block(first_block) &&
    test_free_two_blocks(first_block) &&
    test_expand_region(first_block) &&
    test_complex_expend_region(first_block)};
    return results;
}