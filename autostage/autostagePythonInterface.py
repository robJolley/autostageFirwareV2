import tkinter as tk
import serial
import time

def send_heartbeat():
	ser.write(bytes(b'{HB}'))
	time.sleep(0.1)
	while True:
		n =(ser.readline()) # Stict indenting required......
		if n.split(bytes(b'<HB>\n')):
			print(n)
			break
		if time.time() > timeout:
			print("Timedout")
			break
def write_linear10():
	ser.write(bytes(b'{btgoto 114100}'))
	time.sleep(0.1)
	while True:
		n =(ser.readline())
		if n.split(bytes(b'<btgoto ack>\n')):
			print(n)
			break
		if time.time() > timeout:
			print("Timedout_Lin")
			break
def write_angular10():
	ser.write(bytes(b'{btgoto 100110}'))
	time.sleep(0.1)
	while True:
		n =(ser.readline())
		if n.split(bytes(b'<btgoto ack>\n')):
			print(n)
			break
		if time.time() > timeout:
			print("Timedout_ang")
			break
			
def write_linearm10():
	ser.write(bytes(b'{btgoto 160100}'))
	time.sleep(0.1)
	while True:
		n =(ser.readline())
		if n.split(bytes(b'<btgoto ack>\n')):
			print(n)
			break
		if time.time() > timeout:
			print("Timedout_ang")
			break
			
def write_anglin():
	ser.write(bytes(b'{btgoto 140280}'))
	time.sleep(0.1)
	while True:
		n =(ser.readline())
		if n.split(bytes(b'<btgoto ack>\n')):
			print(n)
			break
		if time.time() > timeout:
			print("Timedout_ang")
			break
			
def send_info():
	ser.write(bytes(b'{btinfo}'))
	time.sleep(0.1)
	while True:
		n =(ser.readline()) # Stict indenting required......
#	if n.split(bytes(b'<HB>\n')):
		print(n)
		break
def quitter():
	ser.close()
	print("Weve come to the end")
	root.destroy()
timeout = time.time() + 5
ser = serial.Serial(port='COM3') # Adjust serial port to requirment
time.sleep(2)
			
root = tk.Tk()
frame = tk.Frame(root)
frame.pack()
tk.Text(root, height= 5, width = 40)

#tk.Insert((END, "Test......\n")

button = tk.Button(frame, 
                   text="QUIT", 
                   fg="red",
                   command=quitter)
button.pack(side=tk.LEFT)
	
button = tk.Button(frame, 
                   text="Heartbeat", 
                   command=send_heartbeat)
button.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Info",
                   command=send_info)
slogan.pack(side=tk.LEFT)

button.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Linear + 10",
                   command=write_linear10)
slogan.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Linear - 10",
                   command=write_linearm10)
slogan.pack(side=tk.LEFT)

slogan = tk.Button(frame,
                   text="Linear and Angular  + 10",
                   command=write_anglin)
slogan.pack(side=tk.LEFT)



button.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Angular_10",
                   command=write_angular10)
slogan.pack(side=tk.LEFT)

slogan.pack(side=tk.LEFT)


root.mainloop()