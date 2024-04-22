import socket

# Server IP and port
host = '0.0.0.0'  # Listen on all available interfaces
port = 12345

# Create a TCP server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen(1)

print(f"Server listening on port {port}...")

# Accept connection from the client
conn, addr = server.accept()
print(f"Connected to client at {addr}")

try:
    while True:
        # Receive data from the client
        data = conn.recv(1024)
        if not data:
            break

        # Decode the received data and strip leading/trailing whitespace
        data_str = data.decode().strip()

        # Split the data string into a list of values
        data_list = data_str.split(",")

        # Initialize a counter to process chunks of 7 values at a time
        for i in range(0, len(data_list), 7):
            # Extract a chunk of 7 values
            chunk = data_list[i:i + 7]

            # Check if the chunk has exactly 7 values
            if len(chunk) == 7:
                try:
                    # Parse each value in the chunk as a float and assign them to variables
                    accel_x = float(chunk[0])
                    accel_y = float(chunk[1])
                    accel_z = float(chunk[2])
                    gyro_x = float(chunk[3])
                    gyro_y = float(chunk[4])
                    gyro_z = float(chunk[5])
                    temp = float(chunk[6])

                    # Print the parsed sensor data for the current set
                    print(f"Accel: X={accel_x:.2f}, Y={accel_y:.2f}, Z={accel_z:.2f}")
                    print(f"Gyro: X={gyro_x:.2f}, Y={gyro_y:.2f}, Z={gyro_z:.2f}")
                    print(f"Temperature: {temp:.2f} °C")
                    print("")

                except ValueError:
                    # Handle parsing errors (e.g., non-numeric values)
                    #print(f"Error parsing chunk: {chunk}")
                    continue

            else:
                # If the chunk does not have exactly 7 values, print a message
                #print(f"Unexpected number of values ({len(chunk)}) in chunk: {chunk}")
                continue


except KeyboardInterrupt:
    print("Stopping server")

finally:
    # Clean up connections
    conn.close()
    server.close()
    print("Server stopped")
