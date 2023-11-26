#ifndef __ced_util_hash_h__
#define __ced_util_hash_h__

#include <stdlib.h>
#include <stdint.h>

#define ced_hash_djb2_str(str) ced_hash_djb2(str, strlen(str))
#define ced_hash_jenkins_str(str) ced_hash_jenkins(str, strlen(str))
#define ced_hash_murmur_str(str) ced_hash_murmur(str, strlen(str), 0)
#define ced_hash_fnv1a_str(str) ced_hash_fnv1a(str, strlen(str))

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
uint32_t ced_hash_murmur(const void *key, size_t length, uint32_t seed);

/**
 * @brief Hashes a string using the FNV1a algorithm
 * @param key The key to hash
 * @param length The length of the key
 * @return The hash of the string
 */
uint32_t ced_hash_fnv1a(const void *key, size_t length);

#endif /* __ced_util_hash_h__ */