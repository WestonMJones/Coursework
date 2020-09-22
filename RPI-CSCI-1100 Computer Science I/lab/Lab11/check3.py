from tkinter import *
from Ball import *
from random import *

class BallDraw(object):
    def __init__ (self, parent):
        ##=====DATA RELEVANT TO BALL===============
        ##  We are going to repeatedly draw a ball object on the canvas,
        ##  "moving" it across the canvas.  The ball object is specified
        ## by (a) its x and y center coordinates (a tuple), (b) its radius,
        ##  (c) the delta x and delta y to move the ball in each time
        ## increment, and (d)  its color.
        
        self.colorList = ["blue", "red", "green", "yellow", "magenta", "orange"]
        self.balls = []
        
        for i in range(10):
            ball = Ball(randint(10,390),randint(10,390),randint(-8,8),randint(-8,8),randint(5,10),choice(self.colorList))
            self.balls.append(ball)
            
        
        #self.ball = Ball(80,200,6,-3,10,"red")
        #self.ball_x,self.ball_y = 80,200    # initial location
        #self.ball_radius = 10
        #self.ball_dx,self.ball_dy = 6,-3    # the movement of the ball object
        #self.ball_color = "red"

        #========DATA NEEDED FOR ANIMATION=========
        #  Here is the time in milliseconds between consecutive instances
        #  of drawing the ball.  If this time is too small the ball will
        #  zip across the canvas in a blur.
        self.wait_time = 100 

        #this will allow us to stop moving the ball when the program quits
        self.isstopped = False 

        self.maxx = 400 # canvas width, in pixels
        self.maxy = 400 # canvas height, in pixels

        #=============CREATE THE NEEDED GUI ELEMENTS===========
        ##  Create a frame, attach a canvas and 4 buttons to this frame
        ##  Buttons are used to cleanly exit the program;
        ##  to speed up or slow down the animation, and to restart 
        ##  the animation.
        ##  Canvas, like an image, is an object that we can draw objects on.
        ##  This canvas is called chart_1.  
        ##  Parent = root window, contains a frame
        ##  The frame contains the canvas and the 4 buttons.
        ##  We only care about the canvas in our animation
        self.parent = parent
        self.frame = Frame(parent)
        self.frame.pack()
        self.top_frame = Frame(self.frame)
        self.top_frame.pack(side=TOP)
        self.canvas = Canvas(self.top_frame, background="white", \
                             width=self.maxx, height=self.maxy )
        self.canvas.pack()
        self.bottom_frame = Frame(self.frame)
        self.bottom_frame.pack(side=BOTTOM)
        self.restart = Button(self.bottom_frame, text="Restart", command=self.restart)
        self.restart.pack(side=LEFT)
        self.slow = Button(self.bottom_frame, text="Slower", command=self.slower)
        self.slow.pack(side=LEFT)
        self.fast = Button(self.bottom_frame, text="Faster", command=self.faster)
        self.fast.pack(side=LEFT)
        self.quit = Button(self.bottom_frame, text="Quit", command=self.quit)
        self.quit.pack(side=RIGHT)

    def faster(self):
        if self.wait_time > 2:
            self.wait_time //= 2

    def slower(self):
        self.wait_time *= 2
            
    def restart(self):
        self.isstopped = False
        for ball in self.balls:
            ball.x = ball.ox
            ball.y = ball.oy
            ball.dx = ball.odx
            ball.dy = ball.ody
        self.animate()
        
    def quit(self):
        self.isstopped = True
        self.parent.destroy()
        
    

    def animate(self):
        ##  Loop until the ball runs off the screen.
        while not self.isstopped:
            self.canvas.delete("all")
            for ball in self.balls:
                bounding_box = ball.bounding_box()
                self.canvas.create_oval(bounding_box, fill=ball.color)
                ball.move()
                ball.check_and_reverse(self.maxx,self.maxy)                
            self.canvas.update()
            self.canvas.after(self.wait_time)
            
          
            


if __name__ == "__main__":
    ##  We will create a root object, which will contain all 
    ##  our user interface elements
    ##
    root = Tk()
    root.title("Tkinter: Lab 11")

    ## Create a class to handle all our animation
    bd = BallDraw(root)

    ## Run the animation by continuously drawing the ball and then moving it
    bd.animate()

    ## This is an infinite loop that allows the window to listen to
    ## "events", which are user inputs.  The only user event here is
    ## closing the window, which ends the program. 
    root.mainloop()