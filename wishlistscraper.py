import re
import json
import requests
import numpy as np
import matplotlib.pyplot as plt

username = input('Enter your username: ')
maxOutput = input('Enter how many discounted games to show: ')

url = "https://store.steampowered.com/wishlist/id/" + username + "/#sort=order"
wishlist_url = json.loads(re.findall(r'g_strWishlistBaseURL = (".*?");', requests.get(url).text)[0])
entries = 0
total_discounts = 0

data = requests.get(wishlist_url + 'wishlistdata/?p=0').json()
json.dumps(data, indent=5)

game_dict = {}
all_discounts = []
all_games = []
all_prices = []

if data.get('success'): # success = 2 means there is no data to recieve from Steam
    is_public = False
    print('Wishlist is empty or private.')
else:
    is_public = True
    print('\n' + username + ' has a public wishlist!' + '\n')
            
if(is_public):
    for i in data:
        entries += 1
        game_name = data[i]['name']
        
        if data[i]['reviews_percent'] != 0:
            game_reviews = data[i]['reviews_percent']
        else:
            game_reviews = 'No reviews.'
            
        if len(data[i]['subs']) != 0:
            game_price = "€{:,.2f}".format(data[i]['subs'][0]['price'] / 100)
            game_discount = str(data[i]['subs'][0]['discount_pct'])
        else:
            game_price = '/'
            game_discount = '0'
        game_dict[entries] = [game_name, game_reviews, game_price, game_discount]
    
sorted_dict = sorted(game_dict.values(), key = lambda x:x[3])

for i in sorted_dict:
    if int(i[3]) > 0:
        total_discounts += 1
        if len(all_games) < int(maxOutput) and len(all_prices) < int(maxOutput) and len(all_discounts) < int(maxOutput):
            all_games.append(i[0])
            all_prices.append(i[2])
            all_discounts.append(i[3])

print('Total wishlists: ' + str(entries) + '\n')
print('Total discounted games: ' + str(total_discounts))

for i in range(len(all_games)):
    plt.text(i, all_discounts[i], all_prices[i], ha = 'center', Bbox = dict(facecolor = '#69a6ce', alpha = 1))
    
plt.rcParams["figure.figsize"] = (14, 6)
plt.bar(all_games, all_discounts)

plt.xticks(rotation = 90) 
plt.title('Show ' + str(maxOutput) + ' discounted wishlist items from ' + username)
plt.ylabel('Discount in %')

plt.show()
