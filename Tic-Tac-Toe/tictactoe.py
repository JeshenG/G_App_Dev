# Group: C0mpt0n
# Group rep: Jeshen Appanna (215001320)
# Tic Tac Toe !


import turtle
import math

import threading
from threading import Thread
p1=""
p2=""
s1=0
s2=0

countMoves=0  # remove if display function is removed
winner=""


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
    global p1
    global p2
    turtle.setup(1080,650)
    wn= turtle.Screen()
    wn.setworldcoordinates(-14,-10,14,10)
    wn.bgpic("chalkboard.gif")
    wn.addshape("letterO.gif")
    wn.addshape("letterX.gif")
    wn.addshape("replay.gif")
    wn.addshape("pen.gif")
    p1=wn.textinput("Text Input !","Enter player 1 name")
    p2=wn.textinput("Text Input !","Enter player 2 name")
    
    board= [["e","e","e"],
            ["e","e","e"],
            ["e","e","e"]]      # "e" means block is empty (note; "o" and "x" will be stored in this list)
    
    countMoves=0         # will be used to increment 1, each time a person clicks on a block
    numMoves=[]
    listWinner=[]
    
    restartBut= turtle.Turtle()
    restartBut.shape("replay.gif")
    restartBut.penup()
    restartBut.speed(10)
    restartBut.goto(-10.5,0)
    restartBut.turtlesize(6)
    restartBut.color("green")
    
    def drawSetup(turtle):
        
        turtle.pencolor("white")   #    ==================================
        turtle.penup()
        turtle.speed(7)
        turtle.shape("pen.gif")
        # space for title
        turtle.goto(-6.5,8.5)
        turtle.write("TIC-TAC-TOE ! -by C0mpt0n",font=("Arial",28,"bold"))
        
        
        turtle.goto(-6,-4) # bottom left corner of board
        turtle.pendown()
        turtle.goto(6,-4)  # bottom right corner of board
        turtle.goto(6,8)   # top right corner of board
        turtle.goto(-6,8)  # top left corner of board
        turtle.goto(-6,-4)  # bottom left corner of board
        
        # draw horixontal lines
        turtle.goto(-6, 0)  # go up 4 units from current point (since dist is 12 units from bottom left to top left)
        turtle.goto(6,0)    # draw line to other side
        turtle.goto(-6,0)   # go back to previous point
        turtle.goto(-6,4)   # go 4 units up
        turtle.goto(6,4)   # draw line
        turtle.goto(-6,4)   # go back
        
        turtle.goto(-6, -4)  # go back to bottom left
        
        # draw vertical lines
        turtle.goto(-2,-4) # go 4 units to right
        turtle.goto(-2, 8)  # draw vertical line
        turtle.goto(-2, -4) # go back to previous point
        turtle.goto(2, -4) # go 4 units to right
        turtle.goto(2, 8) # draw vertical line to point
        
        turtle.penup()
        turtle.goto(10.5,0)
    
    def checkTurn(countMoves):
        if(countMoves % 2==0 or countMoves==0): # if number of plays is even, then its the first person's turn
            return "o"
        else:
            return "x"
        
    
    marker= turtle.Turtle() 
    marker.pensize(6)
    
    drawSetup(marker) 
    marker.penup()
    marker.pencolor("red")
    marker.shape("pen.gif")
    marker.speed(5)
    
    penXO= turtle.Turtle()
    penXO.turtlesize(5)
    penXO.penup()
    penXO.hideturtle()
    penXO.pensize(4)  
    penXO.speed(10)
    
    def getBlockMid(x,y):
        newX= (x+(x+4))/2
        newY= (y+(y+4))/2
        return (newX,newY)
    
    def translate(xCo, yCo):
        row= 0        # create model for turtle screen board and actual list
        col= 0
        # for y values/ row
        if(yCo >-4 and yCo< 0):
            row=2
        if(yCo >0 and yCo< 4):
            row=1
        if(yCo >4 and yCo< 8):
            row=0
        #    for x values/ column
        if(xCo >2 and xCo <6):
            col= 2
        if(xCo >-2 and xCo <2):
            col=1
        if(xCo >-6 and xCo <-2):
            col=0
        return (row,col)
    
    listWinner=[]
         # will be x or 
    
    def checkRowCol(first,second,third):
        return (( first !="e") and (first== second) and (second==third) )
    
    
    jim= turtle.Turtle()     # jim is the replay button
    jim.penup()
    jim.color("green")
    jim.hideturtle()
    jim.speed(10)
    
    def turnDisplay_1(moves):
        global countMoves
        jim.goto(-3,-7)
        jim.clear()
        player=""
        if(moves%2 !=0):
            player=p1
        if(moves % 2==0 ):
            player=p2
        if(countMoves !=0):
            jim.write("It is  {0}'s turn".format(player), font=("Arial",20,"bold"))
        
        
    def checkTie(numMoves,winnerList):
        if(numMoves[0]==8 and len(winnerList)==0 ):
            jim.clear()
            jim.goto(-6,-7)
            jim.write("It is a TIE :( ,Press Restart Button", font=("Arial",20,"bold"))
        
    def displayWin(winner):
        global s1
        global s2
        global p1
        global p2
        jim.goto(-6,-7)
        jim.clear() 
        if(winner=="o"):
            winner= p1
            s1=s1+1
        else:
            winner= p2
            s2=s2+1
        jim.write("The winner is :{0} in this round !!!".format(winner), font=("Arial",20,"bold"))
        jim.goto(-6,-8)
        jim.write(p1+" score: "+str(s1),font=("Arial",17,"bold"))
        jim.goto(-6,-9)
        jim.write(p2+" score: "+str(s2), font=("Arial",17,"bold") )
        
     # functions must automatically set count to 9 (if there are matches)
    
    def checkDiagonals():  # uses checkRowCol function
        marker.penup()
        if(checkRowCol(board[0][0],board[1][1], board[2][2])==True):
            marker.goto(-6,8)
            marker.pendown()
            marker.goto(6,-4)
            marker.penup()
            winner= str(board[0][0])
            listWinner.append(winner)
            displayWin(winner)
            
            
        elif(checkRowCol(board[0][2], board[1][1], board[2][0])==True):
            marker.goto(6,8)
            marker.pendown()
            marker.goto(-6,-4)
            marker.penup()
            winner= str(board[0][2])
            listWinner.append(winner)
            displayWin(winner)
            
    def columnsForWin():
       
        marker.penup()
        for col in range(0,2+1):
            if (checkRowCol(board[0][col], board[1][col], board[2][col]) == True):
                if(col==0):
                    marker.goto(-4,-4)
                    marker.pendown()
                    marker.goto(-4,8)
                    
                elif(col==1):
                    marker.goto(0,-4)
                    marker.pendown()
                    marker.goto(0,8)
                    
                elif(col==2):
                    marker.goto(4,-4)
                    marker.pendown()
                    marker.goto(4,8)
                    
                marker.penup()    
                winner= str(board[0][col])
                listWinner.append(winner)
                displayWin(winner)
                
                break
            
    def rowsForWin():
        marker.penup()
        for row in range(0,2+1):
            if (checkRowCol(board[row][0], board[row][1], board[row][2]) == True):
                if(row==0):
                    marker.goto(-6,6)
                    marker.pendown()
                    marker.goto(6,6)
                    
                elif(row==1):
                    marker.goto(-6,2)
                    marker.pendown()
                    marker.goto(6,2)
                    
                elif(row==2):
                    marker.goto(-6,-2)
                    marker.pendown()
                    marker.goto(6,-2)
                    
                marker.penup()    
                winner= str(board[row][0])
                listWinner.append(winner)
                displayWin(winner)
                break
    
    
    def plot_X_Or_O(x,y):
        global countMoves
        
        if(len(numMoves)==0):
            
            numMoves.append(countMoves)
        else:
            numMoves[0]= countMoves
        
        player = checkTurn(numMoves[0])
        
        turnDisplay_1(countMoves)
        
        if(player=="x"):
            penXO.shape("letterX.gif")    # change turtle icon
            
        else:
            penXO.shape("letterO.gif")
            
        xCo= x
        yCo= y
        winner=""
        
        if(len(listWinner)>0):
            winner= listWinner[0]
            
        if(winner==""):    # if there is no winner , continue with clicking process
            try:
                for horiz in range(-6,2+1,4):  # subtract 4
                    for vert in range(-4,4+1,4):  # subtract 4
                        if((xCo> horiz and xCo < horiz+4) and (yCo> vert and yCo< vert+4)):
                            rowAndCol= translate(xCo,yCo)
                            row= int(rowAndCol[0])
                            col= int(rowAndCol[1])
                            if(board[row][col]== "e"):
                                board[row][col]= player
                                countMoves+=1        # keep track of the number of moves
                                mid= getBlockMid(horiz,vert)
                                penXO.goto(mid[0],mid[1])
                                penXO.stamp()
                                #print(board)
                                break
            except:
                print("Please click the box")
                
        checkDiagonals()
        columnsForWin()
        rowsForWin()
        checkTie(numMoves,listWinner)
        print(numMoves[0]," ",len(listWinner))
        
    wn.onclick(plot_X_Or_O)
    
    def restartGame(x,y):
        global countMoves
        global winner
    
        for row in range(0,2+1):
            for col in range(0,2+1):
                board[row][col]="e"
                
        penXO.clear()
        marker.clear()
        drawSetup(marker)
        marker.color("red")
        jim.clear()
        countMoves=0
        if(len(numMoves)>0):
            numMoves.pop() 
        winner=""
        if(len(listWinner)>0):
            #listWinner.pop()
            while(len(listWinner)!=0):
                listWinner.pop()
            
    restartBut.onclick(restartGame)
    wn.mainloop()
    try:           # to stop playing music
        import pygame       
        pygame.mixer.music.stop()
    except:
        print("Pygame was not installed !")
    wn.exitonclick()
    
"""  
if __name__ == '__main__':
    Thread(target = playSound).start()      # implement threading technique to run music and turtle display 
    Thread(target = display).start()
    
    """

    

    
        
        
    
    


    