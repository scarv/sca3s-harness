/* Copyright (C) 2018 SCARV project <info@scarv.org>
 *
 * Use of this source code is restricted per the MIT license, a copy of which 
 * can be found at https://opensource.org/licenses/MIT (or should be included 
 * as LICENSE.txt within the associated archive or repository).
 */

#ifndef __KERNEL_H
#define __KERNEL_H

#include "util.h"

/** @brief The kernel identifier.
  */

#define KERNEL_ID         ( "unknown" )

/** @brief Number of bytes in a plaintext or ciphertext block.
  */

#define KERNEL_SIZEOF_BLK ( 16 )

/** @brief Number of bytes in a cipher key.
  */

#define KERNEL_SIZEOF_KEY ( 16 )

/** @brief Number of bytes of externally supplied randomness.
  */

#define KERNEL_SIZEOF_RND (  0 )

/** @brief Prepare for, or initialise a subsequent encryption operation.
  *        Note that since
  *        a) doing so takes place outside any measurement of, 
  *           and
  *        b) the cipher key and randomness match those supplied to
  *        said encryption operation, this permits pre-computation (e.g., 
  *        of the key schedule) where appropriate.
  * 
  * @param[in]  k the KERNEL_SIZEOF_KEY byte     cipher key
  * @param[in]  r     KERNEL_SIZEOF_RND bytes of randomness
  */

extern void kernel_enc_init( uint8_t* k, uint8_t* r );

/** @brief Prepare for, or initialise a subsequent decryption operation.
  *        Note that since
  *        a) doing so takes place outside any measurement of, 
  *           and
  *        b) the cipher key and randomness match those supplied to
  *        said decryption operation, this permits pre-computation (e.g., 
  *        of the key schedule) where appropriate.
  * 
  * @param[in]  k the KERNEL_SIZEOF_KEY byte     cipher key
  * @param[in]  r     KERNEL_SIZEOF_RND bytes of randomness
  */

extern void kernel_dec_init( uint8_t* k, uint8_t* r );

/** @brief Perform an encryption operation:
  *        encrypt a  plaintext under a cipher key (using some externally
  *        supplied randomness if appropriate), to produce the associated
  *        ciphertext.
  * 
  * @param[out] c the KERNEL_SIZEOF_BLK byte     ciphertext
  * @param[in]  m the KERNEL_SIZEOF_BLK byte      plaintext
  * @param[in]  k the KERNEL_SIZEOF_KEY byte     cipher key
  * @param[in]  r     KERNEL_SIZEOF_RND bytes of randomness
  */

extern void kernel_enc( uint8_t* c, uint8_t* m, uint8_t* k, uint8_t* r );

/** @brief Perform an decryption operation:
  *        decrypt a ciphertext under a cipher key (using some externally
  *        supplied randomness if appropriate), to produce the associated
  *         plaintext.
  * 
  * @param[out] m the KERNEL_SIZEOF_BLK byte      plaintext
  * @param[in]  c the KERNEL_SIZEOF_BLK byte     ciphertext
  * @param[in]  k the KERNEL_SIZEOF_KEY byte     cipher key
  * @param[in]  r     KERNEL_SIZEOF_RND bytes of randomness
  */

extern void kernel_dec( uint8_t* m, uint8_t* c, uint8_t* k, uint8_t* r );

#endif
