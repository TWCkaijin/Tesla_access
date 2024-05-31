import random
import time



p = int(input("Enter the prime number:"))
g = int(input("Enter the generator:"))

b = random.randint(1,100)

pub = (g**b)%p

server_pub = int(input("Enter the server's public key:"))
sym_key = server_pub**b%p

print(f'sym_key: {sym_key}\nclient_pub: {pub}')
msg = 123

att1 = msg*sym_key*1
print(f'att1: {att1}')

token = int(input("Enter the token:"))
att2 = token*sym_key*2*token
print(f'att2: {att2}')