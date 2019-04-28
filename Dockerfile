# Use osixia/light-baseimage
# sources: https://github.com/osixia/docker-light-baseimage
FROM osixia/alpine-light-baseimage:0.1.6

# Keepalived version
ARG KEEPALIVED_VERSION=2.0.15

# Download, build and install Keepalived
RUN apk --no-cache add \
    autoconf \
    curl \
    gcc \
    ipset \
    ipset-dev \
    iptables \
    iptables-dev \
    libnfnetlink \
    libnfnetlink-dev \
    libnl3 \
    libnl3-dev \
    make \
    musl-dev \
    openssl \
    openssl-dev \
    && curl -o keepalived.tar.gz -SL http://keepalived.org/software/keepalived-${KEEPALIVED_VERSION}.tar.gz \
    && mkdir -p /container/keepalived-sources \
    && tar -xzf keepalived.tar.gz --strip 1 -C /container/keepalived-sources \
    && cd container/keepalived-sources \
    && ./configure --disable-dynamic-linking \
    && make && make install \
    && cd - && mkdir -p /etc/keepalived \
    && rm -f keepalived.tar.gz \
    && rm -rf /container/keepalived-sources \
    && apk --no-cache del \
    autoconf \
    curl \
    gcc \
    ipset-dev \
    iptables-dev \
    libnfnetlink-dev \
    libnl3-dev \
    make \
    musl-dev \
    openssl-dev
 
ADD docker/keepalived.conf /usr/local/etc/keepalived/keepalived.conf

# set keepalived as image entrypoint with --dont-fork and --log-console (to make it docker friendly)
# define /usr/local/etc/keepalived/keepalived.conf as the configuration file to use
ENTRYPOINT ["/usr/local/sbin/keepalived", "--dont-fork", "--log-console", "-f", "/usr/local/etc/keepalived/keepalived.conf"]

