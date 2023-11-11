import os
from cryptography.fernet import Fernet

# Load key 	
with open('key.txt', 'rb') as key_file:
    key = key_file.read()
	
f = Fernet(key)
with open('key.txt', 'wb') as key_file:
    key_file.write(key)

with open('Application.bin', 'rb') as file:
    original = file.read() 

encrypted = f.encrypt(original)

with open('encrypted.bin', 'wb') as encrypted_file:
    encrypted_file.write(encrypted)