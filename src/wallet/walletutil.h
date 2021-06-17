// Copyright (c) 2017 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MIRACLE_WALLET_UTIL_H
#define MIRACLE_WALLET_UTIL_H

#include <fs.h>
#include <vector>

//! Get the path of the wallet directory.
fs::path GetWalletDir();

//! Get wallets in wallet directory.
std::vector<fs::path> ListWalletDir();

#endif // MIRACLE_WALLET_UTIL_H
