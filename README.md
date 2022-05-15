# tex

A C++ game engine for cellular automata 

## Using tex

To use `tex` in your project, clone the library source to your project, and add the following lines in your `CMakeLists.txt` file:

```cmake
add_subdirectory("path/to/tex")
target_link_libraries(your_target PUBLIC/PRIVATE tex::tex)
```

`tex` has many targets which you can link to. Link to whichever fits your needs best.

| Target name   | Description                            |
| ------------- | -------------------------------------- |
| `tex::tex`    | Standard target. Same as `tex::static` |
| `tex::static` | Static library                         |
| `tex::shared` | Shared library                         |
