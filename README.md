ConbiniCoin 1.0.15
================

What is ConbiniCoin?
------------------

[ConbiniCoin](https://conbinicoin.com/) is an implementation of the "[Zerocash](https://github.com/zcash/zips/raw/master/protocol/protocol.pdf)" protocol forked from [ZCash](https://z.cash/).
Based on Bitcoin's code, it intends to offer a far higher standard of privacy
through a sophisticated zero-knowledge proving scheme that preserves
confidentiality of transaction metadata. 

This software is the ConbiniCoin client. It downloads and stores the entire history
of ConbiniCoin transactions; depending on the speed of your computer and network
connection, the synchronization process could take a day or more once the
blockchain has reached a significant size.

License
-------

ConbiniCoin is released under the terms of the MIT license.

See [LICENSE](LICENSE) for more information or see [http://opensource.org/licenses/MIT](http://opensource.org/licenses/MIT).

Get started
-----------

## Linux

### Install dependencies

On Ubuntu/Debian-based systems:
```{r, engine='bash'}
$ sudo apt-get install \
      build-essential pkg-config libc6-dev m4 g++-multilib \
      autoconf libtool ncurses-dev unzip git python \
      zlib1g-dev wget bsdmainutils automake
```

On Fedora-based systems:
```{r, engine='bash'}
$ sudo dnf install \
      git pkgconfig automake autoconf ncurses-devel python \
      python-zmq wget gtest-devel gcc gcc-c++ libtool patch
```

### Fetch the software and parameter files

Fetch our repository with git and run ```fetch-params.sh``` like so:
```{r, engine='bash'}
$ git clone https://github.com/conbinicoin-project/conbinicoin.git
$ cd conbinicoin/
$ git checkout v1.0.15
$ ./zcutil/fetch-params.sh
```

### Build

Ensure you have successfully installed all system package dependencies as described above. Then run the build, e.g.:
```{r, engine='bash'}
$ ./zcutil/build.sh -j$(nproc)
```

This should compile our dependencies and build ```conbinicoind```. (Note: if you don't have ```nproc```, then substitute the number of cores on your system. If the build runs out of memory, try again without the ```-j``` argument, i.e. just ```./zcutil/build.sh```. )

### Configuration

Create the ```~/.conbinicoin``` directory and place a configuration file at ```~/.conbinicoin/conbinicoin.conf``` using the following commands:
```{r, engine='bash'}
$ mkdir -p ~/.conbinicoin
$ echo "addnode=88.86.186.158" > ~/.conbinicoin/conbinicoin.conf
$ echo "rpcuser=username" >> ~/.conbinicoin/conbinicoin.conf
$ echo "rpcpassword=`head -c 32 /dev/urandom | base64`" >> ~/.conbinicoin/conbinicoin.conf
```

### Enabling CPU mining:

If you want to enable CPU mining, run these commands:

```{r, engine='bash'}
$ echo 'gen=1' >> ~/.conbinicoin/conbinicoin.conf
$ echo "genproclimit=-1" >> ~/.conbinicoin/conbinicoin.conf
```

Setting ```genproclimit=-1``` mines on the maximum number of threads possible on your CPU. If you want to mine with a lower number of threads, set ```genproclimit``` equal to the number of threads you would like to mine on.

### Running ConbiniCoin:

Now, run conbinicoind!

```{r, engine='bash'}
$ ./src/conbinicoind
```

To run it in the background (without the node metrics screen that is normally displayed) use ```./src/conbinicoind --daemon```.

You should be able to use the RPC after it finishes loading. Here's a quick way to test:

```{r, engine='bash'}
$ ./src/conbinicoin-cli getinfo
```

To see the peers you are connected to:
```{r, engine='bash'}
$ ./src/conbinicoin-cli getpeerinfo
```

### Additional operations for conbinicoin-cli

As ConbiniCoin is an extension of bitcoin, conbinicoin-cli supports all commands that are part of the Bitcoin Core API (as of version 0.11.2), [https://en.bitcoin.it/wiki/Original_Bitcoin_client/API_calls_list](https://en.bitcoin.it/wiki/Original_Bitcoin_client/API_calls_list)

To list all ConbiniCoin commands, use ```./src/conbinicoin-cli help```.

To get help with a particular command, use ```./src/conbinicoin-cli help <command>```.


### Windows

- Download Windows release binary [here](https://conbinicoin.com/downloads/conbinicoin-1014-win64.zip)
- Download parameter file [here](https://conbinicoin.com/downloads/sprout.zip) and uncompress the content inside the folder ```"C:\Users\%username%\AppData\Roaming\ConbiniCoinParams"```
- Manually edit the ```conbinicoin.conf``` file inside the folder ```"C:\Users\%username%\AppData\Roaming\ConbiniCoin"```
- Run ```conbinicoind.exe``` 
- Optionally run the Java Wallet GUI (already provided inside the download release binary)  ```LitecoinzSwingWalletUI.cmd``` 


### Do you need a Wallet GUI?

A Java Wallet GUI is available [here](https://github.com/conbinicoin-project/conbinicoin-wallet).


DONATIONS
---------

Donations for supporting developers are welcome: 

- LTC: LgSbGGqru5LVHE3cWcgwZDLjr3WorGahr3
- BTC: 1N2rQimKbeUQA8N2LU5vGopYQJmZsBM2d6
- ZEC: t1T8hAYzLNwe2rLQpFMjx9z9FHFd6oQ86P9
- BTG: GNkwW2uS4ed7cofz94J8PrTXJnZgmk5nr2
- BTCZ: t1cmr2QUMCEBRhUVrZHsgC6DnrdzC2FyHz7

Thanks


Security Warnings
-----------------

**ConbiniCoin is experimental and a work-in-progress.** Use at your own risk.

Participation in the ConbiniCoin project is subject to a
[Code of Conduct](code_of_conduct.md).

TO DO
-----
- QT Wallet
- Backports from Bitcoin 0.12+
