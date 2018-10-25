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
ser = serial.Serial(port='COM4') # Adjust serial port to requirment
time.sleep(2)
			
root = tk.Tk()
frame = tk.Frame(root)
frame.pack()
tk.Text(root, height= 5, width = 40)

T.insert((END, "Test......\n")

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
slogan.pack(side=tk.LEFT)


root.mainloop()


