FROM ubuntu:latest
RUN apt-get update && apt-get install -y g++ make cmake libcurl4-openssl-dev sqlite3 libsqlite3-dev
WORKDIR /app
COPY . /app
CMD ["bash"]
