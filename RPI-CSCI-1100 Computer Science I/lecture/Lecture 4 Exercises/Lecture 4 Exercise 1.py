#This program turns the phrase "Things you wish you knew as a Freshman" into
# hashtag form --> "#ThingsYouWishYouKnewAsAFreshman"

phrase = 'Things you wish you knew as a freshman'
hashtag = "#" + phrase.title().replace(" ","")
print("The phrase \"",phrase,"\"",sep='')
print("becomes the hashtag \"",hashtag,"\"",sep='')