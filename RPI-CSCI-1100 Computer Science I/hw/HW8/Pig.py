"""
Class that contains attributes for pigs in the angry birds simulation
"""
class Pig(object):
    def __init__( self, n, x0, y0, r0 ):
        """
        Pig initialization method -- takes name, x position, y position and radius
        """
        self.name = n
        self.x = float(x0)
        self.y = float(y0)
        self.radius = float(r0)