FROM ubuntu
RUN set -x && \
    apt-get update && \
    apt-get install -y python golang wget less && \
    mkdir /root/dcj_tool && \
    cd /root/dcj_tool && \
    wget https://codejam.withgoogle.com/codejam/contest/static/dcj_linux.tar.bz && \
    tar jxvf dcj_linux.tar.bz && \
    echo 'alias dcj=/root/dcj_tool/dcj.sh' >> /root/.bashrc
