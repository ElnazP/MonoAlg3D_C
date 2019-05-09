//
// Created by sachetto on 01/11/18.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "data_utils.h"

#define COMPRESED_BLOCK_SIZE 1 << 15

#ifdef COMPILE_ZLIB
void calculate_blocks_and_compress_data(size_t total_data_size_before_compression,
                                        size_t *total_data_size_after_compression, unsigned char *data_to_compress,
                                        unsigned char **compressed_buffer, size_t *num_blocks,
                                        size_t *block_size_uncompressed, size_t **block_sizes_compressed,
                                        size_t *last_block_size, int compression_level) {

    size_t block_size = COMPRESED_BLOCK_SIZE;

    *total_data_size_after_compression = 0;

    if(total_data_size_before_compression < COMPRESED_BLOCK_SIZE) {
        block_size = total_data_size_before_compression;
    }

    assert(block_size);

    (*block_size_uncompressed) = block_size;

    size_t num_full_blocks = total_data_size_before_compression / block_size;
    *last_block_size = total_data_size_before_compression % block_size;

    *num_blocks = num_full_blocks + (*last_block_size ? 1 : 0);

    *block_sizes_compressed = (size_t *)malloc(sizeof(size_t) * (*num_blocks));

    size_t compressed_data_size = compressBound(total_data_size_before_compression);
    *compressed_buffer = (unsigned char *)malloc(compressed_data_size);

    unsigned char *data_to_compress_pointer = data_to_compress;
    unsigned char *compressed_buffer_pointer = *compressed_buffer;

    size_t uncompressed_data_size = (*block_size_uncompressed);
    size_t local_compressed_data_size = compressBound(uncompressed_data_size);

    for(size_t i = 0; i < *num_blocks; i++) {

        if((i == *num_blocks - 1) && *last_block_size != 0) {
            uncompressed_data_size = *last_block_size;
            local_compressed_data_size = compressBound(uncompressed_data_size);
        }

        (*block_sizes_compressed)[i] =
            compress_buffer(data_to_compress_pointer, uncompressed_data_size, compressed_buffer_pointer,
                            local_compressed_data_size, compression_level);

        data_to_compress_pointer += uncompressed_data_size;
        compressed_buffer_pointer += (*block_sizes_compressed)[i];
        *total_data_size_after_compression += (*block_sizes_compressed)[i];
    }
}


size_t uncompress_buffer(unsigned char const* compressed_data,
                                        size_t compressed_size,
                                        unsigned char* uncompressed_data,
                                        size_t uncompressed_size)
{
    uLongf us = (uLongf) (uncompressed_size);
    Bytef* ud = uncompressed_data;
    const Bytef* cd = compressed_data;
    uLong cs = (uLong)(compressed_size);

    // Call zlib's uncompress function.
    if(uncompress(ud, &us, cd, cs) != Z_OK) {
        printf("Zlib error while uncompressing data.\n");
        return 0;
    }

    // Make sure the output size matched that expected.
    if(us != (uLongf)uncompressed_size ) {
        printf("Decompression produced incorrect size.\n Expected %zu and got %ul\n", uncompressed_size, us);
        return 0;
    }

    return (size_t) us;
}

size_t compress_buffer(unsigned char const *uncompressed_data, size_t uncompressed_data_size,
                       unsigned char *compressed_data, size_t compressed_buffer_size, int level) {
    uLongf cs = (uLongf)compressed_buffer_size;
    Bytef *cd = compressed_data;
    const Bytef *ud = uncompressed_data;
    uLong us = (uLong)(uncompressed_data_size);

    // Call zlib's compress function
    if(compress2(cd, &cs, ud, us, level) != Z_OK) {
        printf("Zlib error while compressing data.\n");
        return 0;
    }

    return (size_t)(cs);
}
#else
size_t compress_buffer(unsigned char const *uncompressed_data, size_t uncompressed_data_size,
                       unsigned char *compressed_data, size_t compressed_buffer_size, int level) {
    return 0;
}
void calculate_blocks_and_compress_data(size_t total_data_size_before_compression,
                                        size_t *total_data_size_after_compression, unsigned char *data_to_compress,
                                        unsigned char **compressed_buffer, size_t *num_blocks,
                                        size_t *block_size_uncompressed, size_t **block_sizes_compressed,
                                        size_t *last_block_size, int compression_level) {
    return;
}
#endif

int invert_bytes(int data) {
    int swapped = ((data >> 24) & 0xff) |      // move byte 3 to byte 0
                  ((data << 8) & 0xff0000) |   // move byte 1 to byte 2
                  ((data >> 8) & 0xff00) |     // move byte 2 to byte 1
                  ((data << 24) & 0xff000000); // byte 0 to byte 3
    return swapped;
}

void read_binary_point(void *source, struct point_3d *p) {

    int data = invert_bytes(*(int *)source);
    p->x = *(float *)&(data);

    source+=4;

    data = invert_bytes(*(int *)source);
    p->y = *(float *)&(data);

    source+=4;

    data = invert_bytes(*(int *)source);
    p->z = *(float *)&(data);


}

sds write_binary_point(sds output_string, struct point_3d *p) {
    int a = *(int *)&(p->x);
    int swapped = invert_bytes(a);

    output_string = sdscatlen(output_string, &swapped, sizeof(int));

    a = *(int *)&(p->y);
    swapped = invert_bytes(a);

    output_string = sdscatlen(output_string, &swapped, sizeof(int));

    a = *(int *)&(p->z);
    swapped = invert_bytes(a);

    output_string = sdscatlen(output_string, &swapped, sizeof(int));

    return output_string;
}

sds write_binary_line (sds output_string, struct line *l)
{
    int a = 2;
    int swapped = invert_bytes(a);
    output_string = sdscatlen(output_string, &swapped, sizeof(int));

    a = *(int *)&(l->source);
    swapped = invert_bytes(a);

    output_string = sdscatlen(output_string, &swapped, sizeof(int));

    a = *(int *)&(l->destination);
    swapped = invert_bytes(a);

    output_string = sdscatlen(output_string, &swapped, sizeof(int));

    return output_string;
}

void get_data_block_from_compressed_vtu_file(uint64_t *raw_data, void* values) {

    uint64_t num_blocks = *raw_data;
    raw_data += 1;

    uint64_t block_size_uncompressed = *raw_data;
    raw_data += 1;

    uint64_t last_block_size = *raw_data;
    raw_data += 1;

    uint64_t  *block_sizes_compressed = (uint64_t*)malloc(num_blocks*sizeof(uint64_t));
    uint64_t  data_size_after_compression = 0;

    for(int i = 0; i < num_blocks; i++) {
        block_sizes_compressed[i] =  *raw_data;
        data_size_after_compression += *raw_data;
        raw_data++;
    }
    unsigned char* uncompressed_data = (unsigned char *)values;
    unsigned char const* compressed_data = (unsigned char const*) raw_data;

    for(int i = 0; i < num_blocks; i++) {
        size_t uncompressed_size = block_size_uncompressed;
        if(i == num_blocks - 1 && last_block_size != 0) {
            uncompressed_size = last_block_size;
        }

        uncompress_buffer(compressed_data, block_sizes_compressed[i], uncompressed_data, uncompressed_size);
        uncompressed_data += uncompressed_size;
        compressed_data += block_sizes_compressed[i];
    }

    free(block_sizes_compressed);
}

void get_data_block_from_uncompressed_binary_vtu_file(uint64_t *raw_data, void* values) {
    uint64_t block_size = *raw_data;
    raw_data += 1;
    memcpy(values, raw_data, block_size);

}