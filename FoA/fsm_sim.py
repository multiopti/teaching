# -*- coding: utf-8 -*-
"""
Created on Wed Nov 18 10:48:25 2020

@author: Admin
"""

from tkinter import *
from PIL import ImageTk,Image  
import os

root = Tk() # In order to create an empty window

root.title("Machine simulation")

# Window geometry
root.geometry("1000x800+200+200")

# Declaring Status Variable
status = "Red"


# Creating Text Frame
textframe = LabelFrame(root,text="Machine status",font=("times new roman",24,"bold"),bg="grey",fg="white",bd=5,relief=GROOVE)
textframe.place(x=0,y=150,width=1000,height=150)
textframe.pack

label_text = Label(textframe,text="R",bg="red",font=("times new roman",24,"bold")).grid(row=0,column=0,padx=10,pady=10)



def changered():
    global status
    global textframe
    if (status =='Blue'):
        status = "Red"
        label_text = Label(textframe,text="R",bg="red",font=("times new roman",24,"bold")).grid(row=0,column=0,padx=10,pady=10)
        textframe.pack
        
def changeyellow():
    global status
    global textframe
    if (status =='Red'):
        status = "Yellow"
        label_text = Label(textframe,text="Y",bg="yellow",font=("times new roman",24,"bold")).grid(row=0,column=0,padx=10,pady=10)
        textframe.pack

    
def changegreen():
    global status
    global textframe
    if (status =='Yellow'):
        status = "Green"
        label_text = Label(textframe,text="G",bg="green",font=("times new roman",24,"bold")).grid(row=0,column=0,padx=10,pady=10)
        textframe.pack
            
def changeblue():
    global status
    global textframe
    if (status =='Green'):
        status = "Blue"
        label_text = Label(textframe,text="B",bg="blue",font=("times new roman",24,"bold")).grid(row=0,column=0,padx=10,pady=10)
        textframe.pack
    
              
    
# Creating Button Frame
buttonframe = LabelFrame(root,text="Control panel",font=("times new roman",24,"bold"),bg="grey",fg="white",bd=5,relief=GROOVE)
buttonframe.place(x=0,y=0,width=1000,height=150)

# Inserting Red Button
playbtn = Button(buttonframe,text="RB",command=changered,width=10,height=1,font=("times new roman",16,"bold"),fg="black",bg="red").grid(row=0,column=0,padx=10,pady=5)
# Inserting Yellow Button
playbtn = Button(buttonframe,text="YB",command=changeyellow,width=10,height=1,font=("times new roman",16,"bold"),fg="black",bg="yellow").grid(row=0,column=1,padx=10,pady=5)
# Inserting Green Button
playbtn = Button(buttonframe,text="GB",command=changegreen,width=10,height=1,font=("times new roman",16,"bold"),fg="black",bg="green").grid(row=0,column=2,padx=10,pady=5)
# Inserting Blue Button
playbtn = Button(buttonframe,text="BB",command=changeblue,width=10,height=1,font=("times new roman",16,"bold"),fg="black",bg="blue").grid(row=0,column=3,padx=10,pady=5)
        

       

imageframe = LabelFrame(root,text="FSM model",font=("times new roman",24,"bold"),bg="grey",fg="white",bd=5,relief=GROOVE)
imageframe.place(x=0,y=300,width=1000,height=500)
        
PIL_image = Image.open("control.jpg")

img = ImageTk.PhotoImage(PIL_image)

# Create a Label Widget to display the text or Image
labelimage = Label(imageframe, image = img)
labelimage.pack()

  
root.mainloop()