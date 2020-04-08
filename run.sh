# Easy run for the application
clang-7 -pthread -lm -o main main.c src/CORE.c src/STORAGE.c src/SetupEra.c

./main
