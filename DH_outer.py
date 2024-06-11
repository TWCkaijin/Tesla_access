import random
import time



p = int(input("Enter the prime number:"))
g = int(input("Enter the generator:"))

b = random.randint(2,5)
print(f'b: {b}')
pub = (g**b)%p

server_pub = int(input("Enter the server's public key:"))
sym_key = server_pub**b%p

print(f'sym_key: {sym_key}\nclient_pub: {pub}')
msg = 123

att1 = msg*sym_key*1
print(f'att1: {att1}')

token = int(input("Enter the token:"))
real_token = token/sym_key
att2 = token*sym_key*pub
print(f'att2: {att2}')