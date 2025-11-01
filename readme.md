# CipherChat

[![Status](https://img.shields.io/badge/status-archived-lightgrey)](#)  
End-to-end encrypted messaging application developed in [Qt Creator](https://doc.qt.io/qtcreator/) and C++ as part of a master’s program project.  

Archived since January 2021.

---

## Components
- **Communicator:** Client-side GUI application  
- **Server:** Simple server to handle LAN TCP communication between users

---


## Features
- **GUI client messaging app**  
  - Authentication with password at launch  
  - Fetches a list of active users from the LAN server  
  - Establishes a shared secret using **Diffie–Hellman key exchange**  
  - Enables **two-way encrypted communication** with other users using **AES**

---


## Dependencies
- [Crypto++](https://www.cryptopp.com/) – for AES encryption and Diffie–Hellman  
- [Qt](https://www.qt.io/) – GUI framework and application development

---
