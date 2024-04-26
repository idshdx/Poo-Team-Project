### A demo voting system with homomorphic encryption.

What?

Homomorphic encryption allows operations to be performed on encrypted data without decrypting it. 
The result of these operations remains encrypted and can be decrypted later if needed.


The code sample is using Microsoft SEAL, you must have it before you begin.
If you are using CMake and a Unix-based operating system, here are the basic steps:

```
git clone https://github.com/microsoft/SEAL.git
cd SEAL
cmake .
make
sudo make install
```
