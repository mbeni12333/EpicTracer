# EpicTracer

A simple raytracer done in C++

main features :
- Materials (metal, lambertian, Emmisive)
- Depth of field
- Antialiasing
- OpenMP
- Environement map

### How to build

visual studio
```
run generateVs2019.bat
open on visual studio, Make sure to choose config release for openmp to work
```

makefiles
```
run generateMakefiles (.bat on windows, .sh on linux)
make config=realease
binaries are found in bin/
```


![render](imgs/render.png)

![render](imgs/renderEpic.png)
