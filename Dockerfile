FROM debian:jessie

ENV CONBINICOIN_CONF=/home/conbinicoin/.conbinicoin/conbinicoin.conf
ENV CONBINICOIN_DATA /home/conbinicoin/.conbinicoin

RUN set -e && \
  apt-get update -q && \
  apt-get install -q -y apt-transport-https wget && \
  wget -qO - https://conbinicoin.com/conbinicoin.asc | apt-key add - && \
  echo "deb [arch=amd64] https://conbinicoin.com/ jessie main" | tee /etc/apt/sources.list.d/conbinicoin.list && \
  apt-get update -q && \
  apt-get install conbinicoin -q -y && \
  conbinicoin-fetch-params && \
  groupadd -r conbinicoin && \
  useradd -r -m -g  conbinicoin conbinicoin && \
  mv /root/.conbinicoin-params /home/conbinicoin/ && \
  mkdir -p /home/conbinicoin/.conbinicoin/ && \
  chown -R conbinicoin:conbinicoin /home/conbinicoin && \
  apt-get purge -q -y apt-transport-https wget && \
  apt-get clean -q -y && \
  apt-get autoclean -q -y && \
  apt-get autoremove -q -y && \
  rm -rf "/var/lib/apt/lists/*" "/var/lib/apt/lists/partial/*" "/tmp/*" "/var/tmp/*"

VOLUME /home/conbinicoin/.conbinicoin

COPY docker-entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
ENTRYPOINT ["/entrypoint.sh"]

USER conbinicoin

EXPOSE 29332 29333 39332 39333

CMD [ "conbinicoind" ]
