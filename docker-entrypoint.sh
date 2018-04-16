#!/bin/bash
set -e

if [ "$1" = 'conbinicoin-cli' -o "$1" = 'conbinicoind' ]; then
	mkdir -p ${CONBINICOIN_DATA}

	if [ ! -s ${CONBINICOIN_CONF} ]; then
		cat <<-EOF > ${CONBINICOIN_CONF}
		rpcpassword=${CONBINICOIN_RPC_PASSWORD:-`head -c 32 /dev/urandom | base64`}
		rpcuser=${CONBINICOIN_RPC_USER:-conbinicoin}
		mainnet=1
		addnode=mainnet.conbinicoin.com
		EOF
	fi

fi

exec "$@"
