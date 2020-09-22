# A program that, given the length and duration of a fitness run, will calculate
# a user's average pace and average speed.

mins = int(input("Minutes ==> "))
print(mins)
secs = int(input("Seconds ==> "))
print(secs)
miles = float(input("Miles ==> "))
print(miles)
print("")

#calculations for pace
total_secs = mins*60 + secs
secs_per_mile = total_secs/miles
out_mins = int(secs_per_mile//60)
out_secs = int(secs_per_mile%60)

#calculations for speed
hours = total_secs / 60**2
mph = miles/hours

#final print statements
print("Pace is",out_mins,"minutes and",out_secs,"seconds per mile.")
print("Speed is",round(mph,2),"miles per hour.")


#Minutes ==> 53
#Seconds ==> 30
#Miles ==> 6.3
#Pace is 8 minutes and 29 seconds per mile.
#Speed is 7.065420560747664 miles per hour.