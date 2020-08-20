/* Copyright 2020 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "tpm_manufacture.h"

#include "Global.h"
#include "NV_fp.h"
#include "Platform.h"
#include "TPM_Types.h"

#define EK_CERT_NV_START_INDEX 0x01C00000

int tpm_manufactured(void) {
  const uint32_t rsa_ek_nv_index = EK_CERT_NV_START_INDEX;
  const uint32_t ecc_ek_nv_index = EK_CERT_NV_START_INDEX + 1;

  /*
   * If either endorsement certificate is not installed, consider
   * the chip un-manufactured.
   */
  if ((NvIsUndefinedIndex(rsa_ek_nv_index) == TPM_RC_SUCCESS) ||
      (NvIsUndefinedIndex(ecc_ek_nv_index) == TPM_RC_SUCCESS)) {
    return 0;
  }

  return 1;
}