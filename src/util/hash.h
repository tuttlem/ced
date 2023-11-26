#ifndef __ced_util_hash_h__
#define __ced_util_hash_h__

#include <stdlib.h>
#include <stdint.h>

/**
 * @brief Hashes a string using the djb2 algorithm
 * @param str The string to hash
 * @return The hash of the string
 */
uint64_t ced_hash_djb2(const void *key, size_t len);

/**
 * @brief Hashes a string using the Jenkins algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t ced_hash_jenkins(const void *key, size_t length);

/**
 * @brief Hashes a string using the Murmur3 algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t hash_murmur(const void *key, size_t length, uint32_t seed);

/**
 * @brief Hashes a string using the FNV1a algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t hash_fnv1a(const void *key, size_t length);

#endif /* __ced_util_hash_h__ */