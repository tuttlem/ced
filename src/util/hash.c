#include "./hash.h"

/**
 * @brief Hashes a string using the djb2 algorithm
 * @param str The string to hash
 * @return The hash of the string
 */
uint64_t ced_hash_djb2(const void *key, size_t len) {
    uint64_t hash = 5381;
    const unsigned char *str = key;

    while (len--) {
        hash = ((hash << 5) + hash) + *str++;
    }

    return hash;
}

/**
 * @brief Hashes a string using the Jenkins algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t ced_hash_jenkins(const void *key, size_t length) {
    uint32_t hash = 0;
    const uint8_t *data = (const uint8_t *)key;

    for (size_t i = 0; i < length; ++i) {
        hash += data[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    return hash;
}

/**
 * @brief Hashes a string using the Murmur3 algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t ced_hash_murmur(const void *key, size_t length, uint32_t seed) {
    const uint32_t m = 0x5bd1e995;
    const int r = 24;

    uint32_t hash = seed ^ length;
    const uint8_t *data = (const uint8_t *)key;

    while (length >= 4) {
        uint32_t k = *(uint32_t *)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        hash *= m;
        hash ^= k;

        data += 4;
        length -= 4;
    }

    switch (length) {
        case 3: hash ^= data[2] << 16;
        case 2: hash ^= data[1] << 8;
        case 1: hash ^= data[0];
            hash *= m;
    }

    hash ^= hash >> 13;
    hash *= m;
    hash ^= hash >> 15;

    return hash;
}

/**
 * @brief Hashes a string using the FNV1a algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t ced_hash_fnv1a(const void *key, size_t length) {
    const uint32_t offset_basis = 2166136261;
    const uint32_t prime = 16777619;

    uint32_t hash = offset_basis;
    const uint8_t *data = (const uint8_t *)key;

    for (size_t i = 0; i < length; ++i) {
        hash ^= data[i];
        hash *= prime;
    }

    return hash;
}