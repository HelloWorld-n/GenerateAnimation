# ABOUT

Displays shape!

# REQUIREMENTS

```shell
sudo apt-get install libsdl2-*
sudo apt-get install clang
```

# RUN

```shell
clang++ src/main.cpp $(pkg-config --cflags --libs sdl2)
./a.out
```
