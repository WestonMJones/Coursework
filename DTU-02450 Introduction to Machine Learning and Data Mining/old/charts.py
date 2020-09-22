import csv

prices = dict()
prices["Manhattan"] = 0
prices["Brooklyn"] = 0
prices["Manhattan"] = 0
prices["Queens"] = 0
prices["Staten Island"] = 0
prices["Bronx"] = 0

count = dict()
count["Manhattan"] = 0
count["Brooklyn"] = 0
count["Manhattan"] = 0
count["Queens"] = 0
count["Staten Island"] = 0
count["Bronx"] = 0

total = 0

with open('AB_NYC_2019.csv', mode='r', encoding="utf8") as csv_file:
    csv_reader = csv.DictReader(csv_file)
    for row in csv_reader:
        total = total + 1
        count[row["neighbourhood_group"]] += 1
        prices[row["neighbourhood_group"]] += int(row["price"])

for key in prices:
    prices[key] = prices[key] / count[key]
    
print(prices)

    