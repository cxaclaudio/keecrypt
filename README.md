<h1>
**KeeCrypt v1.2**
<h1>

KeeCrypt is a security-hardened engine developed in C, focused on Deterministic Key Derivation and identity protection without credential storage (Stateless Auth).

This project was designed to serve as the cryptographic core for applications requiring total anonymity.

<h1>
**Security Hardening**
<h1>
  
Unlike simple hashing engines, KeeCrypt now implements Key Stretching to protect against modern hardware-accelerated attacks:

**1.  PBKDF2-HMAC-SHA256**: Instead of a single hash pass, the engine now performs thousands of iterations using the user's ID as a unique Salt. This makes brute-force attacks via GPU or ASIC computationally expensive.

**2.  Deterministic Salt**: The 3-character ID acts as a cryptographic salt, ensuring that identical passwords produce different Master Keys across different IDs.

**3.  Memory Sanitization**: Uses "OPENSSL_cleanse" to overwrite sensitive buffers in RAM. Unlike "memset", this function is guaranteed not to be optimized away by the compiler.

**4.  Atomic Validation**: Protects against information leakage by validating both Password and ID before providing a generic success/error verdict.


**Entropy Statistics**

The system offers significant resistance against brute-force attacks:

Search Space: ~1.58 x 10¹⁹ combinations.

Offline Resistance: Estimated 25 years to crack via high-end GPU under ideal attack conditions for the minimum required complexity.

**Getting Started**

Prerequisites
The engine depends on the OpenSSL development library.

On Ubuntu/Debian distro:

$ sudo apt update

$ sudo apt install build-essential libssl-dev -y

**Installation and Build**

Clone the repository:

$ git clone https://github.com/cxaclaudio/keecrypt.git

$ cd keecrypt

Compile using the provided Makefile:

$ make

**Usage**

$ ./keecrypt

Enter a password (min. 8 characters, 1 uppercase, 1 symbol).
Enter the 3-character ID (format: 2 digits + 1 lowercase letter, e.g., 11a).

The engine will generate an hexadecimal Master Key.
