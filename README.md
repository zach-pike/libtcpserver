

# How to install
```bash
make build
sudo make install
```
---

# How to compile program g++ that uses libtcpserver
```bash
g++ -std=c++11 -o test.elf program.cpp -ltcpserver
```

### A example program may be found in the `examples` directory under the `lib` directory.