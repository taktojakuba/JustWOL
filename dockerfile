# Dockerfile
FROM gcc:14
WORKDIR /app
COPY listener.cpp ./
RUN g++ -O2 -o listener listener.cpp