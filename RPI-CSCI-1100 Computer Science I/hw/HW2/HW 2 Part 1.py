# The program calculates the amount of oxygen tanks needed
# on a hypothetical trip to mars given the radius of a space capsule, 
# radius of of an oxygen tank and height of an oxygen tank.

# import statements
import math

#functions
def volume_sphere(radius):
    return math.pi * radius**3 * (4/3)

def volume_cylinder(radius, height):
    return math.pi * radius**2 * height

# input statements 
r_cap = float(input("Radius of capsule (m) ==> "))
print(r_cap)
r_oxygen = float(input("Radius of oxygen reservoir (m) ==> "))
print(r_oxygen)
h_oxygen = float(input("Height of oxygen reservoir (m) ==> "))
print(h_oxygen)
print()

#calculations
total_oxygen = volume_sphere(r_cap) * .21 * .41 * 300

oxygen_tank = volume_cylinder(r_oxygen, h_oxygen)*210

tanks = math.ceil(total_oxygen / oxygen_tank)

# final output
print("Oxygen needed for the trip is {0:.3f}m^3.".format(total_oxygen),sep=" ")
print("Each cylinder holds ",round(oxygen_tank,3),"m^3 at 3000 psi.",sep="")
print("The trip will require",tanks,"reservoir tanks.")