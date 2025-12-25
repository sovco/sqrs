# sqrs
Simple qr scan with your webcam

# Build

To build run these commands
```bash
mkdir -p build/deps/nob
curl -Lo build/deps/nob/nob.h https://raw.githubusercontent.com/tsoding/nob.h/refs/heads/main/nob.h
gcc -o project-build project-build.c 
./project-build [--build-tests] [--enable-debug]
```
