// Copyright (c) 2017-2018 The LitecoinZ and ConbiniCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CONBINICOIN_FETCHPARAMS_H
#define CONBINICOIN_FETCHPARAMS_H

#if defined(HAVE_CONFIG_H)
#include "config/bitcoin-config.h"
#endif

#include <string>

void CONBINI_VerifyParams(std::string file, std::string sha256expected);
void CONBINI_FetchParams(std::string url, std::string file);

#endif // CONBINICOIN_FETCHPARAMS_H
