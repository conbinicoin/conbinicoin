// Copyright (c) 2017-2018 The LitecoinZ and ConbiniCoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_CONBINICOINADDRESSVALIDATOR_H
#define BITCOIN_QT_CONBINICOINADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class ConbiniCoinAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ConbiniCoinAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** ConbiniCoin address widget validator, checks for a valid conbinicoin address.
 */
class ConbiniCoinAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit ConbiniCoinAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // BITCOIN_QT_CONBINICOINADDRESSVALIDATOR_H
