def doThis():
    import random
    import turtle
    
    import time #Slow down turtle(which is a snake)
    
    class Square:
        def __init__(self, x, y):
            self.x = x
            self.y = y
    
        def drawself(self, bob):
            bob.color("green")
            bob.goto(self.x - 9, self.y - 9)
            bob.begin_fill()
            for i in range(4):
                bob.forward(18)
                bob.left(90)
            bob.end_fill()
    
    
    class Food:
        def __init__(self, x, y):
            self.x = x
            self.y = y
            self.state = True
    
        def changelocation(self):
         
            self.x = random.randint(0, 20)*20 - 200
            self.y = random.randint(0, 20)*20 - 200
    
        def drawfood(self, food):
            
            food.color("red")
            if self.state == True:
                food.goto(self.x - 9, self.y - 9)
                food.begin_fill()
                for i in range(4):
                    food.forward(18)
                    food.left(90)
                food.end_fill()
    
    class Snake:
        def __init__(self):
            self.headposition = [20, 0] 
            self.body = [Square(-20, 0), Square(0, 0), Square(20, 0)] 
            self.nextX = 1 
            self.nextY = 0
            self.crashed = False 
            self.nextposition = [self.headposition[0] + 20*self.nextX, self.headposition[1] + 20*self.nextY]
    
        def move(self):
            if Square(self.nextposition[0], self.nextposition[1]) not in self.body: 
                self.body.append(Square(self.nextposition[0], self.nextposition[1]))
                del self.body[0]
                self.headposition[0], self.headposition[1] = self.body[-1].x, self.body[-1].y 
                self.nextposition = [self.headposition[0] + 20*self.nextX, self.headposition[1] + 20*self.nextY]
                
            else:
                self.crashed = True
    
        def moveup(self): 
            self.nextX = 0
            self.nextY = 1
    
        def moveleft(self):
            self.nextX = -1
            self.nextY = 0
    
        def moveright(self):
            self.nextX = 1
            self.nextY = 0
    
        def movedown(self):
            self.nextX = 0
            self.nextY = -1
    
        def eatFood(self):
            self.body.append(Square(self.nextposition[0], self.nextposition[1]))
            self.headposition[0], self.headposition[1] = self.body[-1].x, self.body[-1].y
            self.nextposition = [self.headposition[0] + 20*self.nextX, self.headposition[1] + 20*self.nextY]
    
        def drawsnake(self, snake): 
            for block in self.body:
                block.drawself(snake)
    
    
    class Game:
        def __init__(self):
            self.screen = turtle.Screen()
            self.screen.bgcolor("black")
            self.artist = turtle.Turtle()
            self.artist.up()
            self.artist.hideturtle()
            self.snake = Snake()
            self.food = Food(100, 0)
            self.counter = 0 
            self.commandpending = False 
    
        def nextFrame(self):
            while True: 
                game.screen.listen()
                game.screen.onkey(game.snakedown, "Down")
                game.screen.onkey(game.snakeup, "Up")
                game.screen.onkey(game.snakeleft, "Left")
                game.screen.onkey(game.snakeright, "Right")
                turtle.tracer(0) 
                self.artist.clear()
                time.sleep(0.03)
                if self.counter == 5: 
                    if (self.snake.nextposition[0], self.snake.nextposition[1]) == (self.food.x, self.food.y):
                        self.snake.eatFood()
                        self.food.changelocation()
                    else:
                        self.snake.move()
                    self.counter = 0
                else:
                    self.counter += 1
                
                self.food.drawfood(self.artist)
                self.snake.drawsnake(self.artist)
                turtle.update()
                self.commandpending = False
    
        def snakeup(self): 
            if not self.commandpending: 
                self.snake.moveup()
                self.commandpending = True
    
        def snakedown(self):
            if not self.commandpending:
                self.snake.movedown()
                self.commandpending = True
    
        def snakeleft(self):
            if not self.commandpending:
                self.snake.moveleft()
                self.commandpending = True
    
        def snakeright(self):
            if not self.commandpending:
                self.snake.moveright()
                self.commandpending = True
    
    
    game = Game()
    game.nextFrame()
    
    game.screen.mainloop()