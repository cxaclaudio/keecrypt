KeeCrypt v1.0 🔐

KeeCrypt is a minimalist security engine developed in C, focused on Deterministic Key Derivation and identity protection without credential storage (Stateless Auth).

This project was designed to serve as the cryptographic core for applications requiring total anonymity.

🛡️ Security Architecture

KeeCrypt utilizes a Two-Step Validation approach to mitigate information leakage and side-channel attacks:

Silent Input: Uses the Linux termios API to disable terminal echo during password entry, preventing shoulder surfing.

Atomic Validation: The program validates password complexity and ID format but only issues a final verdict after both are entered. This prevents an attacker from knowing which specific field was incorrect.

Robust Hashing: Employs SHA-256 (via OpenSSL) to fuse the Password and the ID into a unique 256-bit Master Key.

Memory Sanitization: Implements buffer clearing via memset to ensure secrets do not remain in RAM after processing.

📊 Entropy Statistics

The system offers significant resistance against brute-force attacks:

Search Space: ~1.58 x 10¹⁹ combinations.

Offline Resistance: Estimated 25 years to crack via high-end GPU under ideal attack conditions for the minimum required complexity.

🚀 Getting Started

Prerequisites
The engine depends on the OpenSSL development library.

On Ubuntu/Debian distro:

$ sudo apt update
$ sudo apt install build-essential libssl-dev -y

Installation and Build
Clone the repository:

$ git clone https://github.com/cxaclaudio/keecrypt.git
$ cd keecrypt

Compile using the provided Makefile:
$ make

🛠️ Usage

Bash
$ ./keecrypt

Enter a password (min. 8 characters, 1 uppercase, 1 symbol).
Enter the 3-character ID (format: 2 digits + 1 lowercase letter, e.g., 11a).

The engine will generate an hexadecimal Master Key.
