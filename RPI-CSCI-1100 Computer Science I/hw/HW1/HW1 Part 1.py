#A program designed to compare informaton about a specific planet in relation to the Earth and Sun. 

#variable declaration for planet
planet_name = "Jupiter"
planet_diameter = 88846
planet_distance = 483632000

#variable declaration for the Earth
earth_diameter = 7926
earth_distance = 92957100

#variable declaration for the Sun
sun_diameter = 864938

#variable declaration for math
pi = 3.14159
c = 186000

print("Sun-to-",planet_name," radius ratio: ",round((sun_diameter/2)/(planet_diameter/2),2),sep='')
print("Sun-to-Earth radius ratio:",round((sun_diameter/2)/(earth_diameter/2),2))
print(planet_name,"-to-Earth radius ratio: ",round((planet_diameter/2)/(earth_diameter/2),2) ,sep='')

print("")

print(planet_name,"-to-Earth Sun distance ratio: ",round(planet_distance/earth_distance,2),sep="")
print("Sun-to-",planet_name," volume ratio: ",round(((4/3)*pi*(sun_diameter/2)**3)/((4/3)*pi*(planet_diameter/2)**3),2) ,sep="")
print("Sun-to-Earth volume ratio:",round(((4/3)*pi*(sun_diameter/2)**3)/((4/3)*pi*(earth_diameter/2)**3),2))
print(planet_name,"-to-Earth volume ratio: ",round(((4/3)*pi*(planet_diameter/2)**3)/((4/3)*pi*(earth_diameter/2)**3),2) ,sep="")

print("")

print("Sun to Earth light travel time in minutes:",round((earth_distance/c)/60,2) )
print("Sun to",planet_name,"light travel time in minutes:", round((planet_distance/c)/60,2))

#Sun-to-Jupiter radius ratio: <number>
#Sun-to-Earth radius ratio: <number>
#Jupiter-to-Earth radius ratio: <number>

#Jupiter-to-Earth Sun distance ratio: <number>
#Sun-to-Jupiter volume ratio: <number>
#Sun-to-Earth volume ratio: <number>
#Jupiter-to-Earth volume ratio: <number>

#Sun to Earth light travel time in minutes: <number>
#Sun to Jupiter light travel time in minutes: <number>
