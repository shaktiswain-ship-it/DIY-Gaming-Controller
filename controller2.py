import serial
import pydirectinput

# Configuration: Map Arduino pins to Keyboard Keys
# Pin 2=D, 3=S, 4=Space, 5=W, 6=A
key_map = {
    "2": "d", "3": "a", "4": "space", "5": "w", "6": "s" 
}

# Change 'COM3' to your Arduino's port
ser = serial.Serial('COM5', 9600, timeout=1)

print("Controller Active! Press Ctrl+C to stop.")

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print(f"Arduino said:{line}") 
        if len(line) >= 2:
            pin = line[:-1]   # The number (e.g., "2")
            action = line[-1] # The action ("P" for press, "R" for release)
            
            if pin in key_map:
                key = key_map[pin]
                if action == "P":
                    pydirectinput.keyDown(key)
                else:
                    pydirectinput.keyUp(key)