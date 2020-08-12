# this will be the main frame   

import turtle

import tictactoe
import snakes
import threading
from threading import Thread

def playSound():
    try:
        import pygame
        #pygame.mixer.init(48009)  # +- 50000   bitrate
        pygame.mixer.init()
        pygame.mixer.music.load("bgSound.wav")
        pygame.mixer.music.play(-1,0.0)     # allows for loop
        while pygame.mixer.music.get_busy() == True:
            continue
    except:
        print("No pygame installed !!!")

def display():        
    turtle.setup(1080,650)
    mainScr= turtle.Screen()
    #mainScr.bgpic("")
    
    mainScr.setworldcoordinates(-10,-10,10,10)
    
    mainScr.addshape("tic.gif")
    mainScr.addshape("snakes.gif")
    mainScr.bgpic("arcade.gif")
    
    
    tictac = turtle.Turtle()
    snake= turtle.Turtle()
    
    tictac.penup()
    snake.penup()
    
    
    tictac.goto(-5, 9)
    tictac.write("C0MPT0N ARCADE !",font=("Arial",24,"bold"))
    
    tictac.goto(-6, 0)
    tictac.shape("tic.gif")
    
    snake.goto(6,0)
    snake.shape("snakes.gif")
    
    
    def playXO(x,y):
        mainScr.bye()
        print("xo clicked")
        if __name__ == '__main__':
            tictactoe.display() 
    tictac.onclick(playXO)
    
    def playSnake(x,y):
        mainScr.bye()
        print("snakes clicked")
        
        if __name__ == '__main__':
            snakes.doThis()    
            
    snake.onclick(playSnake)
    mainScr.mainloop()
    mainScr.exitonclick()
    
if __name__ == '__main__':
    Thread(target = playSound).start()      # implement threading technique to run music and turtle display 
    Thread(target = display).start()
    
    




