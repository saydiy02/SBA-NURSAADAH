import socket

def prime(n):
  if n <= 1:
    return False
  for u in range(2, int(n**0.5)+1):
    if n % u ==0:
      return False
  return True

def udp_server():
  s_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s_add = ('', 5000)
  s_socket.bind(s_add)
  print('UDP server is running.....')

  while True:
    data, c_add = s_socket.recvfrom(1024)
    num = int(data.decode())

    if prime(num):
      result = f'{num} is a Prime Number.'
    
    else:
      result = f'{num} is NOT a prime number.'

    s_socket.sendto(result.encode(), c_add)

udp_server()
