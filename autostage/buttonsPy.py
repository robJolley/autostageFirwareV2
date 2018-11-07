import tkinter as tk
    

def write_slogan():
    print("Tkinter is easy to use!")

root = tk.Tk()
frame = tk.Frame(root)
frame.pack()

button = tk.Button(frame, 
                   text="QUIT", 
                   fg="red",
                   command=quit)
button.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Hello",
                   command=write_slogan)
slogan.pack(side=tk.LEFT)

button.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Linear + 10",
                   command=write_linear10)
slogan.pack(side=tk.LEFT)

button.pack(side=tk.LEFT)
slogan = tk.Button(frame,
                   text="Angular_10",
                   command=write_angular10)
slogan.pack(side=tk.LEFT)

root.mainloop()