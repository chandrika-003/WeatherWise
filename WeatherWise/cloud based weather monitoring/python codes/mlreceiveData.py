import socket

# Create a TCP/IP socket
server_address = ('', 12345)  # Use an empty string to accept connections from any network interface
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.bind(server_address)
sock.listen(1)

while True:
    print("Waiting for connection...")
    connection, client_address = sock.accept()
    try:
        print("Connection from", client_address)
        while True:
            data = connection.recv(1024)
            if data:
                sensor_data = data.decode().split(',')
                if len(sensor_data) == 6:
                    temperature = float(sensor_data[0])
                    pressure = float(sensor_data[1])
                    altitude = float(sensor_data[2])
                    sea_level_pressure = float(sensor_data[3])
                    real_altitude = float(sensor_data[4])
                    rain_intensity = int(sensor_data[5])
                    
                    print("Temperature:", temperature)
                    print("Pressure:", pressure)
                    print("Altitude:", altitude)
                    print("Sea Level Pressure:", sea_level_pressure)
                    print("Real Altitude:", real_altitude)
                    print("Rainfall Intensity:", rain_intensity)
                else:
                    print("Incomplete sensor data received")
            else:
                break
    finally:
        connection.close()
