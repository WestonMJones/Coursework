class Ball(object):
    def __init__ (self,x,y,dx,dy,r,c):
        self.x = x
        self.y = y
        self.dx = dx
        self.dy = dy
        self.radius = r
        self.color = c
        
        #For checkpoint 3
        self.ox = x
        self.oy = y
        self.odx = dx
        self.ody = dy
    
    def position(self):
        return (self.x,self.y)
    
    def move(self):
        self.x += self.dx
        self.y += self.dy
    
    def bounding_box(self):
        x0 = self.x - self.radius
        y0 = self.y - self.radius
        x1 = self.x + self.radius
        y1 = self.y + self.radius
        return (x0, y0, x1, y1)
    
    def get_color(self):
        return self.color
    
    def some_inside(self,maxx,maxy):
        if 0 < self.x + self.radius and \
              self.x - self.radius < maxx and \
              0 < self.y + self.radius and \
              self.y - self.radius < maxy:
            return True
        return False
    
    def check_and_reverse(self,maxx,maxy):
        #If left or right hit
        if 0 > self.x - self.radius or maxx < self.x + self.radius:
            self.dx = self.dx * -1
        elif 0 > self.y - self.radius or maxy < self.y + self.radius:
            self.dy = self.dy * -1
        
    