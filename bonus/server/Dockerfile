FROM ubuntu:latest
EXPOSE 8070
RUN apt-get update && apt-get install -y gcc make
WORKDIR /app
COPY . /app
RUN make
CMD ["./workguard"]