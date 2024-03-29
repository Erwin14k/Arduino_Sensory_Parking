import serial
import time



class Service:
    def __init__(self):
        self.serMASTER = serial.Serial('COM2', 9600, timeout=1)
        self.serLDR = serial.Serial('COM8', 9600, timeout=1)
        self.serLED = serial.Serial('COM6', 9600, timeout=1)

        self.serMASTER.flush()
        self.serLDR.flush()
        self.serLED.flush()


    def writeMASTER(self, msg):
        self.serMASTER.write(msg.encode('utf-8')+b"\r\n")
        time.sleep(0.1)
    
    def writeLDR(self, msg):
        self.serLDR.write(msg.encode('utf-8')+b"\r\n")
        time.sleep(0.1)
    
    def writeLED(self, msg):
        self.serLED.write(msg.encode('utf-8')+b"\r\n")
        time.sleep(0.1)

    def readMASTER(self):
        self.serMASTER.flush()
        return self.serMASTER.readline().decode('utf-8').rstrip()

    def readLDR(self):
        self.serLDR.flush()
        return self.serLDR.readline().decode('utf-8').rstrip()

    def readLED(self):
        self.serLED.flush()
        return self.serLED.readline().decode('utf-8').rstrip()

    def closeMaster(self):
        self.serMASTER.close()

    def closeLDR(self):
        self.serLDR.close()

    def closeLED(self):
        self.serLED.close()

    def time(self):
        return time.strftime("%H:%M:%S", time.localtime())

service = Service()


import requests
import json
class API:
    def __init__(self):
        self.data = ""
        self.base_url = "http://3.144.214.162:5000/"
        self.parqueos_reservados = 0
    
    def get_all_reserved(self):
        url ="get-all-reserved"
        data= ""
        converted_data = ""
        try:
            response_API = requests.get(self.base_url+url)
            data = response_API.text
            parse = json.loads(data)
            self.parqueos_reservados = len(parse)
            

            lista_reservados  =[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
            for p in parse:
                lista_reservados[int(p-1)] = 1;

            for i in lista_reservados:
                converted_data += str(i)

            print("API DATA: "+converted_data)

            return converted_data   
        except Exception as e:
            print("Error: "+str(e))
            return "00000000000000000000000000000000"


    def post_parking_change(self, parqueos):
        url = "change-parking-proteus"
        response = ""
        for parqueo in parqueos:
            body = {
                "id": int(parqueo)
            }

            try:
                response_API = requests.post(self.base_url+url, json=body)
                print(response_API.text)
                response += response_API.text
            except:
                pass
        return response

    def get_parking_alarm(self):
        url = "get-alarm-status"
        data = ""
        converted_data = ""
        try:
            response_API = requests.get(self.base_url+url)
            data = response_API.text
            parse = json.loads(data)
            
            index =-1;
            converted_data = str(parse[0]) + ";" +str(parse[1])
        

            print("ALARM DATA: "+converted_data)
            

            return converted_data
        except Exception as e:
            print("Error: "+str(e))
            return "0;0"
        
        

    
    
        
    





# monitor
import threading

class Monitor:
    def __init__(self, service):
        self.service = service
        self.thread = threading.Thread(target=self.run)
        self.thread.start()
        self.last_ldr = "LDR;00000000000000000000000000000000"
        self.last_led = "LED;00000000000000000000000000000000"
        self.parqueos_reservados= 0
        self.parqueos_ocupados = 0 
        self.parqueos_disponibles = 0 # 32 - (reservados + ocupados)
        self.api = API()

    def run(self):
        while True:
            entrada_master = self.service.readMASTER()
            entrada_ldr = self.service.readLDR()
            entrada_led = self.service.readLED()
            print(self.service.time(),"@ MASTER >" ,entrada_master)
            print(self.service.time(),"@ LDR    >" ,entrada_ldr)
            print(self.service.time(),"@ LED    >" ,entrada_led)

            if entrada_ldr.startswith("LDR;"):
                print("LDR DATA DETECTED")
                self.compareLDR(entrada_ldr)


            if entrada_led.startswith("LED;"):
                print("LED DATA DETECTED")
                comandos = []
                comandos = entrada_led.split(";")
                #comandos[1] = parqueo
                #comandos[2] = estado
                if(comandos[2] == "1"): #1 = reservar #0 = liberar
                    self.agregarReserva(comandos[1])
                else:
                    self.liberarReserva(comandos[1])

            
            print("API CHECKs")
            self.compareLED("LED;"+self.api.get_all_reserved())
            self.compareAlarm(self.api.get_parking_alarm())
            self.parqueos_reservados = self.api.parqueos_reservados
            self.parqueos_disponibles = 32 - (self.parqueos_reservados + self.parqueos_ocupados)
            
            data_parqueos = str(self.parqueos_disponibles)+";"+str(self.parqueos_reservados)+";"+str(self.parqueos_ocupados)
            print("PARQUEOS: "+data_parqueos)
            self.service.writeMASTER("P;"+data_parqueos)
            time.sleep(1)
    
    def compareLDR(self, entrada_ldr):
        self.parqueos_ocupados = entrada_ldr.count("1")
        
        print("\t-Comparando LDR")
        data_to_send = "";
        parqueos_diferentes = []
        # comparar entrada_ldr con el ultimo valor de entrada_ldr
        if entrada_ldr != self.last_ldr:
            print("\t\t- LDR cambiado")
            #buscar que indice es distinto
            for i in range(4, len(entrada_ldr)):
                if entrada_ldr[i] != self.last_ldr[i]:
                    data_to_send+= "1"
                    
                else:
                    data_to_send+= "0"


            for i in range(len(data_to_send)):
                if data_to_send[i] == "1":
                    parqueos_diferentes.append(i+1)
            print("\t\t- Data to send: ", data_to_send, " Parqueos diferentes: ", parqueos_diferentes)

            # iterar parqueos diferentes [2,4,6]
            
            self.api.post_parking_change(parqueos_diferentes)
            


            
            self.last_ldr = entrada_ldr
        
        else:
            print("\t\t- LDR sin cambios")
            
    def compareLED(self, entrada_led):
        print("\t-Comparando LED")
        data_to_send = "";
        parqueos_diferentes = []
        # comparar entrada_led con el ultimo valor de entrada_led
        if entrada_led != self.last_led:
            print("\t\t- LED cambiado")
            #buscar que indice es distinto
            for i in range(4, len(entrada_led)):
                if entrada_led[i] != self.last_led[i]:
                    data_to_send+= "1"
                    
                else:
                    data_to_send+= "0"


            for i in range(len(data_to_send)):
                if data_to_send[i] == "1":
                    parqueos_diferentes.append(i+1)
            print("\t\t- Data to send: ", data_to_send, " Parqueos reservados: ", parqueos_diferentes)
            
            self.service.writeLED(entrada_led)    
            self.last_led = entrada_led
        else:
            print("\t\t- LED sin cambios")


    def compareAlarm(self, status):
        # if(status == "1;0"):

        # else{
            
        # }
        self.service.writeLED(str(status))


    
        
        
        

        

                

# main

monitor = Monitor(service)
monitor.thread.join()
