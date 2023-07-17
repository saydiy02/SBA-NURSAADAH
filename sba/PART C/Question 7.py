import socket

def udp_client():
  c_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  s_add = ('localhost', 5000)

  range_s = int(input('Enter the starting number: '))
  range_e = int(input('Enter the ending number: '))

  for num in range (range_s, range_e +1):
    c_socket.sendto(str(num).encode(), s_add)
    result,_ = c_socket.recvfrom(1024)
    print(result.decode())

  c_socket.close()

udp_client()
