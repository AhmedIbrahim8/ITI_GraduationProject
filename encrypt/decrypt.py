import os
from cryptography.fernet import Fernet

# Load key 
with open('key.txt', 'rb') as key_file:
    key = key_file.read()

f = Fernet(key) 

with open('encrypted.bin', 'rb') as encrypted_file:
    encrypted = encrypted_file.read()

decrypted = f.decrypt(encrypted)

with open('decrypted.bin', 'wb') as decrypted_file:
   decrypted_file.write(decrypted)