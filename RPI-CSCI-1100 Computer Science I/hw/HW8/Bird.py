"""
Class that contains attributes and methods for birds in the angry birds simulation
"""

import math
#name|mass|x0|y0|radius|dx|dy

class Bird(object):
    def __init__( self, n, m, x0,y0,r,dx0,dy0 ):
        """
        Initialization method for bird class -- takes the name, mass, starting x position, starting y position, radius, initial
        x velocity, and initial y velocity.
        """
        self.name = n
        self.mass = float(m)
        self.x = float(x0)
        self.y = float(y0)
        self.radius = float(r)
        self.dx = float(dx0)
        self.dy = float(dy0)
    
    def speed(self):
        """
        function that returns the absolute velocity of the bird given
        it's x and y velocity components
        """
        a = self.dx**2
        b = self.dy**2
        c = a + b
        speed = math.sqrt(c)
        return speed
    
    def position(self):
        """
        This function returns the position of the bird in
        "(x,y)" in formatted string form with 1 decimal place
        """
        out_string="({:.1f},{:.1f})".format(self.x,self.y)
        return out_string
    
    def dx_and_dy(self):
        """
        This function returns the x and y velocities of the bird in
        "(dx,dy)" in formatted string form with 1 decimal place
        """        
        out_string="({:.1f},{:.1f})".format(self.dx,self.dy)
        return out_string
        
    def collided(self, other):
        """
        This function returns true if the bird in its current position
        has collided with another object of position (x and y)
        """
        #Use pythagorean theorum to calculate distance given x and y coordinates
        distance = math.sqrt((abs(self.x-other.x)**2)+(abs(self.y-other.y)**2))
        radii_sum = self.radius+other.radius
        
        #If the distance is less than or equal to the sum of each object's radius,
        #then the objects have collided
        if distance<=radii_sum:
            return True
        else:
            return False
        
        
