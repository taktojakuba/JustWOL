# Dockerfile
FROM gcc:14
WORKDIR /app
COPY wol listener.cpp ./
RUN g++ -O2 -o listener listener.cpp