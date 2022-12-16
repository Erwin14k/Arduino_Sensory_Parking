import datetime
import serial
from time import sleep

arduino = serial.Serial(port="COM1", baudrate=9600, timeout=1)

while True:
    data = arduino.readline()

    data = str(data)

    data = data.replace("b'", "")
    data = data.replace("\\r\\n'", "")
    data = data.replace("'", "")

    # get time
    time = datetime.datetime.now()
    time = str(time)
    print(time,"\t", data)

    if(data == "esperando"):
        print("Enviando alarma")
        arduino.write("1".encode())

    sleep(1)
