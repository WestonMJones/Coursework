"""
Class that contains attributes and methods for barriers in the angry birds simulation
"""

class Barrier(object):
    def __init__(self,n,s,xc,yc,r):
        """
        Initialization method for barrier class -- takes name, strength (hitpoints),
        x position for center, y position for center, and radius
        """
        self.name = n
        self.strength = float(s)
        self.x = float(xc)
        self.y = float(yc)
        self.radius = float(r)
    
    def calculate_damage(self, bird):
        """
        Given a bird, this method updates the barrier's strength based on
        how much the given bird inflicts.
        """
        dmg = bird.mass * bird.speed()**2
        self.strength-=dmg
        if self.strength<0:
            self.strength=0
        