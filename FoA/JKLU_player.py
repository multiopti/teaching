# -*- coding: utf-8 -*-
"""
Created on Wed Nov 18 10:48:25 2020

@author: Admin
"""

from tkinter import *
from PIL import ImageTk,Image  
import pygame
import os

class MusicPlayer:   
    def __init__(self,root):
        self.root = root
        # Title of the window
        self.root.title("JKLU Music Player")
        # Window Geometry
        self.root.geometry("1000x400+200+200")
        # Initiating Pygame
        pygame.init()
        # Initiating Pygame Mixer
        pygame.mixer.init()
        # Declaring track Variable
        self.track = StringVar()
        # Declaring Status Variable
        self.status = StringVar()
        self.status.set("-Stopped")
    
        # Creating the Track Frames for Song label & status label
        trackframe = LabelFrame(self.root,text="Song Track",font=("times new roman",15,"bold"),bg="Navyblue",fg="white",bd=5,relief=GROOVE)
        trackframe.place(x=0,y=0,width=600,height=100)
        # Inserting Song Track Label
        songtrack = Label(trackframe,textvariable=self.track,width=27,font=("times new roman",20,"bold"),bg="orange",fg="black").grid(row=0,column=0,padx=10,pady=5)
        # Inserting Status Label
        trackstatus = Label(trackframe,textvariable=self.status,font=("times new roman",20,"bold"),bg="orange",fg="black").grid(row=0,column=1,padx=10,pady=5)
    
        # Creating Button Frame
        buttonframe = LabelFrame(self.root,text="Control Panel",font=("times new roman",15,"bold"),bg="grey",fg="white",bd=5,relief=GROOVE)
        buttonframe.place(x=0,y=100,width=600,height=100)
        # Inserting Play Button
        playbtn = Button(buttonframe,text="PLAY",command=self.playsong,width=10,height=1,font=("times new roman",16,"bold"),fg="navyblue",bg="pink").grid(row=0,column=0,padx=10,pady=5)
        # Inserting Pause Button
        playbtn = Button(buttonframe,text="PAUSE",command=self.pausesong,width=8,height=1,font=("times new roman",16,"bold"),fg="navyblue",bg="pink").grid(row=0,column=1,padx=10,pady=5)
        # Inserting Unpause Button
        playbtn = Button(buttonframe,text="UNPAUSE",command=self.unpausesong,width=10,height=1,font=("times new roman",16,"bold"),fg="navyblue",bg="pink").grid(row=0,column=2,padx=10,pady=5)
        # Inserting Stop Button
        playbtn = Button(buttonframe,text="STOP",command=self.stopsong,width=10,height=1,font=("times new roman",16,"bold"),fg="navyblue",bg="pink").grid(row=0,column=3,padx=10,pady=5)
        
        # Creating Text Frame
        textframe = LabelFrame(self.root,text="Text Frame",font=("times new roman",15,"bold"),bg="grey",fg="white",bd=5,relief=GROOVE)
        textframe.place(x=0,y=200,width=1000,height=200)
        #textframe.pack(fill="both", expand="yes")
        left = Label(textframe, text="Welcome to my music player ...", font=("times new roman",30,"bold"))
        left.pack()
                
        
        # Creating Playlist Frame
        songsframe = LabelFrame(self.root,text="Song Playlist",font=("times new roman",15,"bold"),bg="grey",fg="white",bd=5,relief=GROOVE)
        songsframe.place(x=600,y=0,width=400,height=200)
        # Inserting scrollbar
        scrol_y = Scrollbar(songsframe,orient=VERTICAL)
        # Inserting Playlist listbox
        self.playlist = Listbox(songsframe,yscrollcommand=scrol_y.set,selectbackground="gold",selectmode=SINGLE,font=("times new roman",12,"bold"),bg="silver",fg="navyblue",bd=5,relief=GROOVE)
        # Applying Scrollbar to listbox
        scrol_y.pack(side=RIGHT,fill=Y)
        scrol_y.config(command=self.playlist.yview)
        self.playlist.pack(fill=BOTH)
        # Changing Directory for fetching Songs
        #os.chdir("F://Google Drive//Docencia//Teaching - JKLU//Teaching - 2020//FoA - 2121//Code//music_player//songs")
        os.chdir(".//songs")
        # Fetching Songs
        songtracks = os.listdir()
        # Inserting Songs into Playlist
        for track in songtracks:
          self.playlist.insert(END,track)      
        
    def playsong(self):
        if (self.status.get() == "-Stopped"):
            # Displaying Selected Song title
            self.track.set(self.playlist.get(ACTIVE))
            # Displaying Status
            self.status.set("-Playing")
             # Loading Selected Song
            pygame.mixer.music.load(self.playlist.get(ACTIVE))
            # Playing Selected Song
            pygame.mixer.music.play()
    
    def stopsong(self):
        if (self.status.get() == "-Playing"):
            # Displaying Status
            self.status.set("-Stopped")
            pygame.mixer.music.stop()
        
    def pausesong(self):
        if (self.status.get() == "-Playing"):
            # Displaying Status
            self.status.set("-Paused")
            # Paused Song
            pygame.mixer.music.pause()
    
    def unpausesong(self):
        if (self.status.get() == "-Paused"):
            # It will Display the  Status
            self.status.set("-Playing")
            # Playing back Song
            pygame.mixer.music.unpause()
    
root = Tk() # In order to create an empty window
# Passing Root to MusicPlayer Class
MusicPlayer(root)
    
root.mainloop()