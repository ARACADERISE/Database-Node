# Easy run for the application
# Run bash run.sh to enable ./run on Linux terminal
clang-7 -pthread -lm -o main main.c src/CORE.c src/Node.c src/STORAGE.c src/SetupEra.c

# making run runnable by typing ./run
chmod +x run
